#pragma once
#include "nlohmann/json_fwd.hpp"
#include "rule_clearance_copper.hpp"
#include "rule_clearance_copper_other.hpp"
#include "rule_clearance_silk_exp_copper.hpp"
#include "rule_diffpair.hpp"
#include "rule_hole_size.hpp"
#include "rule_parameters.hpp"
#include "rule_plane.hpp"
#include "rule_track_width.hpp"
#include "rule_via.hpp"
#include "rule_preflight_checks.hpp"
#include "rule_clearance_copper_keepout.hpp"
#include "rules/rules.hpp"
#include "util/uuid.hpp"

namespace horizon {
using json = nlohmann::json;

class BoardRules : public Rules {
public:
    BoardRules();

    void load_from_json(const json &j);
    RulesCheckResult check(RuleID id, const class Board *b, class RulesCheckCache &cache,
                           check_status_cb_t status_cb) const;
    void apply(RuleID id, class Board *b, class ViaPadstackProvider &vpp) const;
    json serialize() const;
    std::set<RuleID> get_rule_ids() const;
    const Rule *get_rule(RuleID id) const override;
    const Rule *get_rule(RuleID id, const UUID &uu) const override;
    std::map<UUID, const Rule *> get_rules(RuleID id) const override;
    void remove_rule(RuleID id, const UUID &uu);
    Rule *add_rule(RuleID id);
    void cleanup(const class Block *block);

    uint64_t get_default_track_width(class Net *net, int layer) const;
    const RuleClearanceCopper *get_clearance_copper(Net *net_a, Net *net_b, int layer) const;
    const RuleClearanceCopperOther *get_clearance_copper_other(Net *net, int layer) const;
    const RuleDiffpair *get_diffpair(NetClass *net_class, int layer) const;
    const RuleClearanceCopperKeepout *get_clearance_copper_keepout(Net *net, const KeepoutContour *contour) const;
    uint64_t get_max_clearance() const;

    const RuleParameters *get_parameters() const;

    UUID get_via_padstack_uuid(const class Net *net) const;
    const ParameterSet &get_via_parameter_set(const class Net *net) const;

    const PlaneSettings &get_plane_settings(const class Net *net, int layer) const;

private:
    std::map<UUID, RuleHoleSize> rule_hole_size;
    std::map<UUID, RuleTrackWidth> rule_track_width;
    std::map<UUID, RuleClearanceCopper> rule_clearance_copper;
    std::map<UUID, RuleVia> rule_via;
    std::map<UUID, RuleClearanceCopperOther> rule_clearance_copper_other;
    std::map<UUID, RulePlane> rule_plane;
    std::map<UUID, RuleDiffpair> rule_diffpair;
    std::map<UUID, RuleClearanceCopperKeepout> rule_clearance_copper_keepout;

    RuleClearanceSilkscreenExposedCopper rule_clearance_silkscreen_exposed_copper;
    RuleParameters rule_parameters;
    RulePreflightChecks rule_preflight_checks;

    RulesCheckResult check_track_width(const class Board *b) const;
    RulesCheckResult check_hole_size(const class Board *b) const;
    RulesCheckResult check_clearance_copper(const class Board *b, class RulesCheckCache &cache,
                                            check_status_cb_t status_cb) const;
    RulesCheckResult check_clearance_copper_non_copper(const class Board *b, class RulesCheckCache &cache,
                                                       check_status_cb_t status_cb) const;
    RulesCheckResult check_preflight(const class Board *b) const;
    RulesCheckResult check_clearance_copper_keepout(const class Board *b, class RulesCheckCache &cache,
                                                    check_status_cb_t status_cb) const;
};
} // namespace horizon
