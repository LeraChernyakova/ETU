#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

// 'TripPlanner' is a class that encapsulates the logic of finding a shortest 
// path between two points given a certain map, all provided through stdin
class TripPlanner
{
private:
   // An auxiliary class that represents a graph to be traversed
   class Map
   {
   public:
      // A location is simply represented as one char, as the problem suggests
      using Location = char;

      // An aouxiliary struct to hold a pair of locations
      // It is used to describe both a single graph edge and a path sought for
      struct Route
      {  Location source;
         Location destination;

         // The comparison op. is necessary for Route to be used as a map key
         bool operator<(const Route &route) const
         {  return this->source < route.source or 
            (this->source == route.source and this->destination < route.destination);
      }  };

      static constexpr unsigned MAX_WEIGHT = -1;  // the underflow is intentional
         
   private:
      std::map<Route, unsigned> routes;  // holds weights of graph edges

   public:
      // 'is_mapped' tests for whether an edge is present in the graph
      unsigned is_mapped(Route route) const
      {  return this->routes.count(route) != 0;  }
      
      // 'weight' retrieves a weight corresponding to a given edge
      // It is also used to introduce a new one
      unsigned get_weight(Route route) const
      {  return this->routes.at(route);  }

      unsigned &get_weight(Route route)
      {  return this->routes[route];  }
   };

   Map map;
   static constexpr Map::Location FIRST_LOCATION_ID = 'a';
   Map::Location last_location_id = FIRST_LOCATION_ID;
   std::vector<Map::Location> trip_plan;
   Map::Route trip_route;

   // The heuristic function for the A* method
   unsigned compute_heuristic_distance(Map::Location location)
   {  return this->trip_route.destination - location;  }

   // 'greedy_planner' recursively finds a solution using a greedy approach
   bool plan_greedily(Map::Route route, bool reset = true)
   {  this->trip_plan.push_back(route.source);
      if(route.source == route.destination)
      {  return true;  }
      static Map discarded_routes;
      if(reset)
      {  discarded_routes = Map();  }
      while(true)
      {  unsigned min_weight = Map::MAX_WEIGHT;
         Map::Route next_route;
         for(Map::Location location = FIRST_LOCATION_ID; 
             location <= this->last_location_id; ++location)
         {  Map::Route new_route{route.source, location};
            if(not this->map.is_mapped(new_route))
            {  continue;  }
            if(discarded_routes.is_mapped(new_route))
            {  continue;  }
            if(map.get_weight(new_route) < min_weight)
            {  min_weight = map.get_weight(new_route);
               next_route = new_route;
         }  }
         if(min_weight == Map::MAX_WEIGHT)
         {  return this->trip_plan.pop_back(), false;  }
         discarded_routes.get_weight(next_route);
         if(plan_greedily({next_route.destination, route.destination}, false))
         {  return true;  }
   }  }

   // 'a_star_planner' finds a solution using the A* approach
   bool plan_using_a_star()
   {  using Tag = std::pair<unsigned, Map::Location>;
      std::map<Map::Location, Tag> tags;
      std::priority_queue<Tag, std::vector<Tag>, std::greater<Tag>> location_queue;
      tags[this->trip_route.source] = {0, 0};
      location_queue.push({0, this->trip_route.source});

      while(not location_queue.empty())
      {  Map::Location source = location_queue.top().second;
         location_queue.pop();
         if(source == this->trip_route.destination)
         {  break;  }
         for(Map::Location destination = FIRST_LOCATION_ID; 
             destination <= this->last_location_id; ++destination)
         {  Map::Route route{source, destination};
            if(not this->map.is_mapped(route))
            {  continue;  }
            unsigned weight = tags[source].first + this->map.get_weight(route);
            if(tags.count(destination) == 0 or weight < tags[destination].first)
            {  tags[destination] = {weight, source};
               weight += compute_heuristic_distance(destination);
               location_queue.push({weight, destination});
      }  }  }

      Map::Location destination = this->trip_route.destination;
      while(destination != 0)
      {  this->trip_plan.push_back(destination);
         destination = tags[destination].second;
      }
      return std::reverse(this->trip_plan.begin(), this->trip_plan.end()), true;
   }

public:
   // The constructor reads the requred data from stdin and initialises the map
   // accordingly
   TripPlanner()
   {  std::cin >> this->trip_route.source >> this->trip_route.destination;

      Map::Location route_source, route_target;
      float weight;
      while(std::cin >> route_source >> route_target >> weight)
      {  this->map.get_weight({route_source, route_target}) = weight;
         this->last_location_id = std::max({
               route_source, route_target, 
               this->last_location_id  });
   }  }

   // 'plan' selects an algorithm to be used and then calls the appropriate
   // method
   TripPlanner &plan(bool use_a_star)
   {
      if(use_a_star)
         this->plan_using_a_star();
      else
         this->plan_greedily(this->trip_route);
      return *this;
   }

   friend std::ostream &operator<<(std::ostream &out, const TripPlanner &tabletop);
};

// Outputs a solution
std::ostream &operator<<(std::ostream &out, const TripPlanner &planner)
{  for(int i = 0; i < planner.trip_plan.size(); i++)
   {  out << planner.trip_plan[i];  }
   return out;
}

int main()
{  return std::cout << TripPlanner().plan(true) << std::endl, 0;  }

