#ifndef __CLUSTER_HH__
#define __CLUSTER_HH__
#include <string>
#include <cstdlib>
#include <cstdint>
#include <sstream>
#include <memory>
#include <fstream>
#include <algorithm>
#include <unordered_set>

#include <dpp/dpp.h>
#include <cluster/command.hh>

namespace cluster
{
	class config {
	public:
		config(uint64_t id, std::string str) {
			serverID = id;
			token = str;
		}
		auto swearwords() -> const std::unordered_set<std::string>& {
			return swear_words;
		}
		void insert(const std::string& str) {
			swear_words.insert(str);
		}
	public:
		uint64_t serverID;
		std::string token;
	private:
		std::unordered_set<std::string> swear_words = {};
	};

	class discord_bot {
	public:
		explicit discord_bot() = default;
		explicit discord_bot(config configuration);
		~discord_bot();
	public:
		const discord_bot* initialize();
	public:
		void ready_t(const dpp::ready_t& ctx);
		void message_create_t(const dpp::message_create_t& ctx);
	public:
		void send_command(commands::command_t& cmd);
	public:
		bool is_swearwords(const std::string& content);
		bool is_command(const std::string& content);
	private:
		std::pair<dpp::cluster*, config> m_cluster = { nullptr, {0x0, ""} };
	};
}
#endif __CLUSTER_HH__ // !__CLUSTER_HH__
