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

#include "utils_NegotiationRoom.hpp"

#include <rmf_traffic/geometry/Circle.hpp>
#include <rmf_traffic/schedule/Database.hpp>
#include <rmf_traffic/schedule/Participant.hpp>

SCENARIO("Test difficult 3-way scenarios")
{
  const std::string test_map_name = "test_map";

  rmf_traffic::agv::Graph graph_a;
  graph_a.add_waypoint(test_map_name, {18.013, -15.518}, true); // 0
  graph_a.add_waypoint(test_map_name, {12.417, -15.536}, true); // 1
  graph_a.add_waypoint(test_map_name, { 9.990, -15.543}, true); // 2
  graph_a.add_waypoint(test_map_name, { 9.482, -15.534}, true); // 3
  graph_a.add_waypoint(test_map_name, {17.934, -20.165}, true); // 4
  graph_a.add_waypoint(test_map_name, {17.943, -21.654}, true); // 5
  graph_a.add_waypoint(test_map_name, {22.370, -21.593}, true); // 6
  graph_a.add_waypoint(test_map_name, {22.370, -22.660}, true); // 7
  graph_a.add_waypoint(test_map_name, {22.399, -23.540}, true); // 8
  graph_a.add_waypoint(test_map_name, {18.968, -20.183}, true); // 9
  graph_a.add_waypoint(test_map_name, {20.137, -20.188}, true); // 10
  graph_a.add_waypoint(test_map_name, { 8.185, -15.535}, true); // 11

  graph_a.add_lane(0, 1);
  graph_a.add_lane(1, 0);
  graph_a.add_lane(1, 2);
  graph_a.add_lane(2, 1);
  graph_a.add_lane(2, 3);
  graph_a.add_lane(3, 2);
  graph_a.add_lane(4, 5);
  graph_a.add_lane(5, 4);
  graph_a.add_lane(5, 6);
  graph_a.add_lane(6, 5);
  graph_a.add_lane(0, 4);
  graph_a.add_lane(4, 0);
  graph_a.add_lane(6, 7);
  graph_a.add_lane(7, 6);
  graph_a.add_lane(7, 8);
  graph_a.add_lane(8, 7);
  graph_a.add_lane(4, 9);
  graph_a.add_lane(9, 4);
  graph_a.add_lane(9, 10);
  graph_a.add_lane(10, 9);
  graph_a.add_lane(3, 11);
  graph_a.add_lane(11, 3);




  rmf_traffic::agv::Graph graph_b;
  graph_b.add_waypoint(test_map_name, {14.052, -23.840}); // 0
  graph_b.add_waypoint(test_map_name, {14.081, -21.636}); // 1
  graph_b.add_waypoint(test_map_name, {10.430, -23.964}); // 2
  graph_b.add_waypoint(test_map_name, {10.432, -21.788}); // 3
  graph_b.add_waypoint(test_map_name, {10.429, -25.995}); // 4
  graph_b.add_waypoint(test_map_name, { 8.093, -23.870}); // 5
  graph_b.add_waypoint(test_map_name, { 8.055, -21.818}); // 6
  graph_b.add_waypoint(test_map_name, { 8.068, -25.961}); // 7
  graph_b.add_waypoint(test_map_name, {14.920, -21.585}); // 8
  graph_b.add_waypoint(test_map_name, {14.918, -23.846}); // 9
  graph_b.add_waypoint(test_map_name, {18.435, -21.633}); // 10
  graph_b.add_waypoint(test_map_name, {18.511, -17.278}); // 11
  graph_b.add_waypoint(test_map_name, {16.830, -17.278}); // 12
  graph_b.add_waypoint(test_map_name, {11.829, -21.687}); // 13
  graph_b.add_waypoint(test_map_name, {11.892, -15.379}); // 14
  graph_b.add_waypoint(test_map_name, {16.876, -15.313}); // 15
  graph_b.add_waypoint(test_map_name, {11.829, -19.079}); // 16

  graph_b.add_lane(0, 1);
  graph_b.add_lane(1, 0);
  graph_b.add_lane(1, 2);
  graph_b.add_lane(2, 1);
  graph_b.add_lane(2, 3);
  graph_b.add_lane(3, 2);
  graph_b.add_lane(2, 4);
  graph_b.add_lane(4, 2);
  graph_b.add_lane(2, 5);
  graph_b.add_lane(5, 2);
  graph_b.add_lane(5, 6);
  graph_b.add_lane(6, 5);
  graph_b.add_lane(5, 7);
  graph_b.add_lane(7, 5);
  graph_b.add_lane(1, 8);
  graph_b.add_lane(8, 1);
  graph_b.add_lane(8, 9);
  graph_b.add_lane(9, 8);
  graph_b.add_lane(8, 10);
  graph_b.add_lane(10, 8);
  graph_b.add_lane(10, 11);
  graph_b.add_lane(11, 10);
  graph_b.add_lane(11, 12);
  graph_b.add_lane(12, 11);
  graph_b.add_lane(13, 1);
  graph_b.add_lane(1, 13);
  graph_b.add_lane(14, 15);
  graph_b.add_lane(15, 14);
  graph_b.add_lane(15, 12);
  graph_b.add_lane(12, 15);
  graph_b.add_lane(14, 16);
  graph_b.add_lane(16, 14);
  graph_b.add_lane(16, 13);
  graph_b.add_lane(13, 16);

  const auto profile_a = rmf_traffic::Profile{
    rmf_traffic::geometry::make_final_convex<
      rmf_traffic::geometry::Circle>(1.5)
  };

  const auto traits_a = rmf_traffic::agv::VehicleTraits{
    {0.45, 0.5}, {0.3, 1.5}, profile_a
  };

  const auto profile_b = rmf_traffic::Profile{
    rmf_traffic::geometry::make_final_convex<
      rmf_traffic::geometry::Circle>(0.3)
  };

  const auto traits_b = rmf_traffic::agv::VehicleTraits{
    {0.4, 3.0}, {0.4, 4.0}, profile_b
  };

  const rmf_traffic::agv::Planner::Configuration config_a{graph_a, traits_a};
  const rmf_traffic::agv::Planner::Configuration config_b{graph_b, traits_b};

  rmf_traffic::schedule::Database database;

  auto a0 = rmf_traffic::schedule::make_participant(
    rmf_traffic::schedule::ParticipantDescription{
      "a0",
      "fleet_a",
      rmf_traffic::schedule::ParticipantDescription::Rx::Responsive,
      profile_a
    }, database);

  auto b1 = rmf_traffic::schedule::make_participant(
    rmf_traffic::schedule::ParticipantDescription{
      "b1",
      "fleet_b",
      rmf_traffic::schedule::ParticipantDescription::Rx::Responsive,
      profile_b
    }, database);

  auto b2 = rmf_traffic::schedule::make_participant(
    rmf_traffic::schedule::ParticipantDescription{
      "b2",
      "fleet_b",
      rmf_traffic::schedule::ParticipantDescription::Rx::Responsive,
      profile_b
    }, database);

  GIVEN("Case 1")
  {
    const auto time = std::chrono::steady_clock::now();

    NegotiationRoom::Intentions intentions;

    auto a0_starts = rmf_traffic::agv::compute_plan_starts(
      graph_a, {18.012, -15.53, -M_PI}, time);

    auto b1_starts = rmf_traffic::agv::compute_plan_starts(
          graph_b, {16.858, -15.758, -M_PI/2.0}, time);

    auto b2_starts = rmf_traffic::agv::compute_plan_starts(
          graph_b, {16.83, -17.26, -M_PI/2.0}, time);

    rmf_traffic::agv::Planner planner_a(
          config_a,
          rmf_traffic::agv::Planner::Options{
            rmf_utils::make_clone<rmf_traffic::agv::ScheduleRouteValidator>(
              database, a0.id(), profile_a)
          });

    REQUIRE(!a0_starts.empty());
    auto plan_a0 = planner_a.plan(a0_starts, {1});
    REQUIRE(plan_a0);
    a0.set(plan_a0->get_itinerary());

    rmf_traffic::agv::Planner planner_b(
          config_b,
          rmf_traffic::agv::Planner::Options(
            rmf_utils::make_clone<rmf_traffic::agv::ScheduleRouteValidator>(
              database, b1.id(), profile_b)
          ));

    auto plan = planner_b.plan(b1_starts, {11});
    REQUIRE(plan);

    intentions.insert({
      a0.id(),
      NegotiationRoom::Intention{std::move(a0_starts), {1}, config_a} });

    intentions.insert({
      b1.id(),
      NegotiationRoom::Intention{std::move(b1_starts), {11}, config_b}});

    intentions.insert({
      b2.id(),
      NegotiationRoom::Intention{std::move(b2_starts), {13}, config_b}});

//    auto room = NegotiationRoom(database, intentions);
//    room.print_failures = true;
//    auto proposal = room.solve();
//    REQUIRE(proposal);
  }







}