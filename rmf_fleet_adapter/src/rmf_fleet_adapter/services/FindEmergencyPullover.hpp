/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef SRC__RMF_FLEET_ADAPTER__SERVICES__FINDEMERGENCYPULLOVER_HPP
#define SRC__RMF_FLEET_ADAPTER__SERVICES__FINDEMERGENCYPULLOVER_HPP

#include "../jobs/SearchForPath.hpp"

namespace rmf_fleet_adapter {
namespace services {

//==============================================================================
class FindEmergencyPullover
{
public:

  FindEmergencyPullover(
      std::shared_ptr<const rmf_traffic::agv::Planner> planner,
      rmf_traffic::agv::Plan::StartSet starts,
      std::shared_ptr<const rmf_traffic::schedule::Snapshot> schedule,
      rmf_traffic::schedule::ParticipantId participant_id);

  using Result = rmf_traffic::agv::Plan::Result;

  template<typename Subscriber>
  void operator()(const Subscriber& s);

  static constexpr double estimate_leeway = 1.01;
  static constexpr double compliance_leeway = 3.0;

private:

  struct ProgressInfo
  {
    double cost = std::numeric_limits<double>::infinity();
    const Result* progress = nullptr;
  };

  struct Evaluator
  {
    bool initialize(const Result& setup);

    bool evaluate(Result& progress);

    void discard(Result& progress);

    ProgressInfo best_estimate;
    ProgressInfo second_best_estimate;
    ProgressInfo best_result;
    std::size_t finished_count = 0;
  };

  std::shared_ptr<const rmf_traffic::agv::Planner> _planner;
  rmf_traffic::agv::Plan::StartSet _starts;
  std::shared_ptr<const rmf_traffic::schedule::Snapshot> _schedule;
  rmf_traffic::schedule::ParticipantId _participant_id;

  std::vector<std::shared_ptr<jobs::SearchForPath>> _search_jobs;
  rxcpp::subscription _search_sub;

  Evaluator _greedy_evaluator;
  Evaluator _compliant_evaluator;
};

} // namespace services
} // namespace rmf_fleet_adapter

#include "detail/impl_FindEmergencyPullover.hpp"

#endif // SRC__RMF_FLEET_ADAPTER__SERVICES__FINDEMERGENCYPULLOVER_HPP