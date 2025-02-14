
#include "live/extract_messages.hpp"

#include <nlohmann/json.hpp>

#include <utility>

std::vector<std::string> extract_danmu_messages(const std::vector<std::string>& messages) {

    std::vector<std::string> danmu_messages;
    danmu_messages.reserve(messages.size()); // 预留空间

    for (auto& message : messages) {

        // // 简单验证
        // if (message.size() < 10 || 
        //     message.substr(0, 5) != "{\"cmd\"") {
        //     continue; 
        // }

        //try {
            nlohmann::json json_message = nlohmann::json::parse(message); 

            auto it = json_message.find("cmd");
            if (it != json_message.end() && it->get<std::string>() == "DANMU_MSG") {
                
                auto& info = json_message["info"];
                if (info.is_array() && info.size() > 1) {
                    // 直接插入结果,避免中间变量
                    danmu_messages.emplace_back(info[1].get_ref<const std::string&>());
                }
            }

        //} catch(const std::exception& e) {
          // 忽略JSON解析错误
        //}
    }
    return danmu_messages;
}