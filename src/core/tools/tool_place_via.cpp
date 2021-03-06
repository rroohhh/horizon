#include "tool_place_via.hpp"
#include "document/idocument_board.hpp"
#include "board/board.hpp"
#include "imp/imp_interface.hpp"
#include <iostream>

namespace horizon {

ToolPlaceVia::ToolPlaceVia(IDocument *c, ToolID tid) : ToolBase(c, tid), ToolPlaceJunction(c, tid)
{
}

bool ToolPlaceVia::can_begin()
{
    return doc.b;
}

bool ToolPlaceVia::begin_attached()
{
    bool r;
    UUID net_uuid;
    std::tie(r, net_uuid) = imp->dialogs.select_net(doc.b->get_block(), false);
    if (!r) {
        return false;
    }
    net = doc.b->get_block()->get_net(net_uuid);
    imp->tool_bar_set_tip("<b>LMB:</b>place via <b>RMB:</b>delete current via and finish");
    return true;
}

void ToolPlaceVia::create_attached()
{
    auto uu = UUID::random();
    const auto &rules = dynamic_cast<BoardRules &>(*doc.b->get_rules());
    auto ps = doc.b->get_via_padstack_provider()->get_padstack(rules.get_via_padstack_uuid(net));
    via = &doc.b->get_board()
                   ->vias.emplace(std::piecewise_construct, std::forward_as_tuple(uu), std::forward_as_tuple(uu, ps))
                   .first->second;
    via->junction = temp;
    via->from_rules = true;
    via->net_set = net;
    via->parameter_set = rules.get_via_parameter_set(net);
    via->expand(*doc.b->get_board());
}

void ToolPlaceVia::delete_attached()
{
    if (via) {
        doc.b->get_board()->vias.erase(via->uuid);
    }
}

bool ToolPlaceVia::update_attached(const ToolArgs &args)
{
    if (args.type == ToolEventType::CLICK) {
        if (args.button == 1) {
            if (args.target.type == ObjectType::JUNCTION) {
                Junction *j = doc.r->get_junction(args.target.path.at(0));
                via->junction = j;
                create_attached();
                return true;
            }
        }
    }
    return false;
}
} // namespace horizon
