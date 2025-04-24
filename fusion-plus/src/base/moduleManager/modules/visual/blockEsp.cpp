#include "blockEsp.h"

#include "moduleManager/commonData.h"
#include "menu/menu.h"
#include "util/math/worldToScreen.h"

void BlockEsp::Update()
{
	if (!settings::BlockESP_Enabled) return;
	if (!CommonData::SanityCheck()) return;

	Vector3 playerPosition = CommonData::playerLastPos + (CommonData::playerPos - CommonData::playerLastPos) * CommonData::renderPartialTicks;

	int xLimit = (int)playerPosition.x + m_range * 2;
	int yLimit = (int)playerPosition.y + m_range * 2;
	int zLimit = (int)playerPosition.z + m_range * 2;

	std::vector<Data> newRenderData;
	for (int x = (int)playerPosition.x - m_range; x < xLimit; x++)
	{
		for (int y = (int)playerPosition.y - m_range; y < yLimit; y++)
		{
			for (int z = (int)playerPosition.z - m_range; z < zLimit; z++)
			{
				CBlock block = SDK::minecraft->theWorld->GetBlock(x, y, z);

				if (block.GetBlockId() == 0 || block.GetBlockId() != settings::BlockESP_TargetID) continue;

				Vector3 blockPos = Vector3((float)x, (float)y, (float)z);

				std::cout << block.GetBlockId() << " found at " << blockPos.x << " " << blockPos.y << " " << blockPos.z << std::endl;

				float dist = playerPosition.Distance(blockPos);
				char distC[32];
				std::snprintf(distC, sizeof(distC), "%.1f", dist);
				std::string distS(distC);

				Data data;
				data.position = blockPos;
				data.name = "";//block.GetBlockName();
				data.dist = dist;
				data.distText = distS + "m";
				data.opacityFadeFactor = 0.0f;

				newRenderData.push_back(data);
			}
		}
	}
	m_renderData = newRenderData;
}

void BlockEsp::RenderOverlay()
{
	if (!settings::BlockESP_Enabled || !CommonData::dataUpdated) return;

	for (Data data : m_renderData)
	{
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 p;
		if (!CWorldToScreen::WorldToScreen(data.position, CommonData::modelView, CommonData::projection, (int)screenSize.x, (int)screenSize.y, p))
		{
			continue;
		}
	}
}

void BlockEsp::RenderMenu()
{
	
}
