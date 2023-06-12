#pragma once
//文件版
#include "../comm/util.hpp"
#include "../comm/log.hpp"
#include "include/mysql.h"

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <cassert>

//根据题目list文件，加载所有题目信息到内存中
// model：主要用来和数据进行交互，对外提供访问数据的接口

namespace ns_model
{
    using namespace ns_util;
    using namespace ns_log;

    struct Question
    {
        std::string number; //题目编号，唯一
        std::string title;  //题目标题
        std::string star;   //难度：简单 中等 困难
        std::string desc;   //题目的描述
        std::string header; //题目预设给用户在线编辑器的代码
        std::string tail;   //题目的测试用例，需要和header拼接，形成完整代码
        int cpu_limit;      //时间要求(S)
        int mem_limit;      //空间要求(KB)
    };

    const std::string oj_questions = "oj_questions";
    const std::string host = "127.0.0.1";
    const std::string user = "oj_client";
    const std::string passwd = "PasswdforThisProj_123";
    const std::string db = "oj";
    const int port = 3306;

    class Model
    {
    public:
        Model()
        {
        }

        bool QueryMysql(const std::string &sql, std::vector<Question> *out)
        {
            // 创建mysql句柄
            MYSQL *my = mysql_init(nullptr);

            // 连接数据库
            if (nullptr == mysql_real_connect(my, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, nullptr, 0))
            {
                LOG(FATAL) << "连接数据库失败"
                           << "\n";
                return false;
            }

            // 设置该连接的编码格式，否则会出现乱码问题
            mysql_set_character_set(my, "utf8");

            LOG(INFO) << "连接数据库成功"
                      << "\n";

            // 执行sql语句
            if (0 != mysql_query(my, sql.c_str()))
            {
                LOG(WARNINGS) << sql << " execute error"
                              << "\n";
                return false;
            }

            //提取结果
            MYSQL_RES *res = mysql_store_result(my);

            // 分析结果
            int rows = mysql_num_rows(res);   //获得行数据
            int cols = mysql_num_fields(res); //获得列数量

            Question q;

            for (int i = 0; i < rows; i++)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                q.number = row[0];
                q.title = row[1];
                q.star = row[2];
                q.desc = row[3];
                q.header = row[4];
                q.tail = row[5];
                q.cpu_limit = atoi(row[6]);
                q.mem_limit = atoi(row[7]);

                out->push_back(q);
            }
            //释放结果空间
            free(res);
            //关闭mysql连接
            mysql_close(my);

            return true;
        }

        bool GetAllQuestions(std::vector<Question> *out)
        {
            std::string sql = "select * from ";
            sql += oj_questions;
            return QueryMysql(sql, out);
        }

        bool GetOneQuestion(const std::string &number, Question *q)
        {
            bool res = false;
            std::string sql = "select * from ";
            sql += oj_questions;
            sql += " where number=";
            sql += number;
            std::vector<Question> result;
            if (QueryMysql(sql, &result))
            {
                if (result.size() == 1)
                {
                    *q = result[0];
                    res = true;
                }
            }
            return res;
        }

        ~Model() {}
    };
}