#include <iostream>
#include <string>
#include <ctemplate/template.h>

int main()
{
    std::string in_html = "./test.html";
    std::string value = "比特就业课";

    // 形成数据字典
    ctemplate::TemplateDictionary root("test"); //unordered_map<> test;
    root.SetValue("key", value);                //test.insert({});

    // 获取被渲染网页对象
    ctemplate::Template *tpl = ctemplate::Template::GetTemplate(in_html, ctemplate::DO_NOT_STRIP);

    // 添加字典数据到网页中
    std::string out_html;
    tpl->Expand(&out_html, &root);

    //完成了渲染
    std::cout << out_html << std::endl;
    return 0;
}


// #include <iostream>
// #include <sys/time.h>
// #include <sys/resource.h>
// #include <unistd.h>
// #include <signal.h>

// #include <jsoncpp/json/json.h>

// int main()
// {
//     //序列化
//     //将结构化数据转化为一个字符串
//     //Value是一个Json的中间类，可以填充KV值
//     Json::Value root;
//     root["code"] = "mycode";
//     root["user"] = "ssj";
//     root["age"] = "18";

//     Json::FastWriter writer;
//     std::string str = writer.write(root);
//     std::cout << str << std::endl;
// }

// // int main()
// // {
// //     //时间限制

// //     // struct rlimit r;
// //     // r.rlim_cur = 1;
// //     // r.rlim_max = RLIM_INFINITY;
// //     // setrlimit(RLIMIT_CPU, &r);
// //     // while (1);
// //     // return 0;

// //     //内存限制
// //     struct rlimit r;
// //     r.rlim_cur = 1024 * 1024 * 40;
// //     r.rlim_max = RLIM_INFINITY;
// //     setrlimit(RLIMIT_AS, &r);
// //     int count = 0;
// //     while (1)
// //     {
// //         int *p = new int[1024 * 1024];
// //         count++;
// //         std::cout << "size: " << count << std::endl;
// //         sleep(1);
// //     }
// //     return 0;
// // }

