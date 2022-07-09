#include "UI/PillowTextureTable/PillowTextureTableData.hpp"
#include "UI/PillowTextureTable/PillowTextureTableCell.hpp"
#include "logging.hpp"

#include "System/Action_2.hpp"

DEFINE_TYPE(CustomPillows, PillowTextureTableData);

namespace CustomPillows {
    void PillowTextureTableData::ctor() {
        reuseIdentifier = StringW("PillowTextureCellList");
    }

    void PillowTextureTableData::Start() {

    }

    HMUI::TableCell* PillowTextureTableData::CellForIdx(HMUI::TableView* tableView, int idx) {
        INFO("Making Cell {}", idx);
        auto tableCell = reinterpret_cast<PillowTextureTableCell*>(tableView->DequeueReusableCellForIdentifier(reuseIdentifier));
        
        if (!tableCell) {
            tableCell = PillowTextureTableCell::CreateNewCell();
        }

        tableCell->set_reuseIdentifier(reuseIdentifier);
        DEBUG("Getting Entry");
        auto entry = texturePairs[idx];
        DEBUG("Getting name");
        auto name = entry.key;
        DEBUG("Getting texture");
        auto texture = entry.value;
        DEBUG("Setting name");
        tableCell->SetText(name);
        DEBUG("Setting texture");
        tableCell->SetTexture(texture);
        DEBUG("Returning");
        return tableCell;
    }

    float PillowTextureTableData::CellSize() {
        return cellSize;
    }

    int PillowTextureTableData::NumberOfCells() {
        if (!textures) return 0;
        return textures->get_Count();
    }
}