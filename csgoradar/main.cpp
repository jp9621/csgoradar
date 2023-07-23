#include "memory.h"
#include <thread>


namespace offsets {
	constexpr auto oLocalPlayer = 0xDEA98C;
	constexpr auto oEntityList = 0x4DFFF7C;
	constexpr auto oTeamNum = 0xF4;
	constexpr auto oSpotted = 0x93D;
}

int main()
{
	const auto memory = Memory{ "csgo.exe" };
	const auto client = memory.GetModuleAddress("client.dll");



	while (true) {
		const auto localPlayer = memory.Read<std::uintptr_t>(client + offsets::oLocalPlayer);
		const auto localTeam = memory.Read<std::uintptr_t>(client + offsets::oTeamNum);

			for (auto i = 1; i <= 64; i++) {
				const auto entity = memory.Read<std::uintptr_t>(client + offsets::oEntityList + i * 0x10);

				if (memory.Read<std::uintptr_t>(entity + offsets::oTeamNum) == localTeam)
					continue;

				memory.Write<bool>(entity + offsets::oSpotted, true);
			}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	



	return 0;
}