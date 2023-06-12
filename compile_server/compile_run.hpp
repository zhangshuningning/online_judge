#pragma once
#include "compiler.hpp"
#include "runner.hpp"
#include "../comm/log.hpp"
#include "../comm/util.hpp"

#include <jsoncpp/json/json.h>

namespace ns_compile_and_run
{
    using namespace ns_log;
    using namespace ns_util;
    using namespace ns_compiler;
    using namespace ns_runner;
    class CompileAndRun
    {
    public:
        static void RemoveTempFile(const std::string &file_name)
        {
            //清理文件的个数是不确定的，但是有哪些是知道的
            std::string _src = PathUtil::Src(file_name);
            if (FileUtil::IsFileExists(_src))
                unlink(_src.c_str());

            std::string _compiler_error = PathUtil::CompilerError(file_name);
            if (FileUtil::IsFileExists(_compiler_error))
                unlink(_compiler_error.c_str());

            std::string _execute = PathUtil::Exe(file_name);
            if (FileUtil::IsFileExists(_execute))
                unlink(_execute.c_str());

            std::string _stdin = PathUtil::Stdin(file_name);
            if (FileUtil::IsFileExists(_stdin))
                unlink(_stdin.c_str());

            std::string _stdout = PathUtil::Stdout(file_name);
            if (FileUtil::IsFileExists(_stdout))
                unlink(_stdout.c_str());

            std::string _stderr = PathUtil::Stderr(file_name);
            if (FileUtil::IsFileExists(_stderr))
                unlink(_stderr.c_str());
        }
        // code>0:进程收到了信号导致异常崩溃
        // code<0:整个过程非运行报错（代码为空，编译报错）
        // code=0:进程收到了信号导致异常崩溃（整个过程全部完成）
        static std::string CodeToDesc(int code, const std::string &file_name)
        {
            std::string desc;
            switch (code)
            {
            case 0:
                desc = "编译运行成功";
                break;
            case -1:
                desc = "提交的代码为空";
                break;
            case -2:
                desc = "未知错误";
                break;
            case -3:
                //代码编译时发生错误
                FileUtil::ReadFile(PathUtil::CompilerError(file_name), &desc, true);
                break;
            case SIGABRT: // 6
                desc = "内存超过范围";
                break;
            case SIGXCPU: // 24
                desc = "CPU使用超时";
                break;
            case SIGFPE: // 8
                desc = "浮点数溢出";
                break;
            default:
                desc = "未知：" + std::to_string(code);
                break;
            }
            return desc;
        }
        /************************************
         * 输入：
         * input:用户给自己提交的代码对应的输入，扩展
         * code：用户提交的代码
         * cpu_limit: 时间要求
         * mem_limit: 空间要求
         * 输出：
         * status：状态码
         * result：请求结果
         * 选填：
         * stdout：程序运行完的结果
         * stderr：程序运行完的错误结果
         * 参数：
         * in_json: {"code": "#include...", "input": "","cpu_limit":1,"mem_limit:10240"}
         * out_json: {"status":"0","reason":"","stdout":"","stderr":""}
         * *********************************/
    public:
        static void Start(const std::string &in_json, std::string *out_json)
        {
            Json::Value in_value;
            Json::Reader reader;
            reader.parse(in_json, in_value); //最后在处理差错问题

            std::string code = in_value["code"].asString();
            std::string input = in_value["input"].asString();
            int cpu_limit = in_value["cpu_limit"].asInt();
            int mem_limit = in_value["mem_limit"].asInt();

            int status_code = 0;
            Json::Value out_value;
            int run_result = 0;
            std::string file_name;

            if (code.size() == 0)
            {
                //最后再处理差错问题
                status_code = -1; //代码为空
                goto END;
            }

            //形成的文件名只具有唯一性，没有目录，没有后缀
            //毫秒级时间戳+原子性递增的唯一值：来保证唯一值
            file_name = FileUtil::UniqFileName();
            //形成临时src文件
            if (!FileUtil::WriteFile(PathUtil::Src(file_name), code))
            {
                status_code = -2; //未知错误
                goto END;
            }

            if (!Compiler::Compile(file_name))
            {
                //编译失败
                status_code = -3; //编译时发生错误
                goto END;
            }

            run_result = Runner::Run(file_name, cpu_limit, mem_limit);
            if (run_result < 0)
            {
                status_code = -2; //未知错误
            }
            else if (run_result > 0)
            {
                status_code = run_result; //运行崩溃
            }
            else
            {
                //运行成功
                out_value["status"] = 0;
            }
        END:
            out_value["status"] = status_code;
            out_value["reason"] = CodeToDesc(status_code, file_name);
            if (status_code == 0)
            {
                //整个过程运行成功
                std::string _stdout;
                FileUtil::ReadFile(PathUtil::Stdout(file_name), &_stdout, true);
                out_value["stdout"] = _stdout;

                std::string _stderr;
                FileUtil::ReadFile(PathUtil::Stderr(file_name), &_stderr, true);
                out_value["stderr"] = _stderr;
            }
            Json::StyledWriter writer;
            *out_json = writer.write(out_value);
            
            RemoveTempFile(file_name);
        }
    };
}