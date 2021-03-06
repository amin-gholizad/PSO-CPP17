#ifndef PSO_H
#define PSO_H
#include <cmath>
#include "particle.hpp"
namespace pso {
  template<ull N,ull S=100>
  std::pair<Particle<N>,std::array<Particle<N>,S>> pso(const vars<N>& lower_bound,const vars<N>& upper_bound,const Problem<N>& problem,const size_t max_iter=1000,const std::array<double,2>& c={0.2,0.2},const std::array<double,2>& iw={0.1,0.01},const double mu=0.1){
    auto w = [&](size_t it){ return ((max_iter - it) - (iw[0] - iw[1]))/max_iter + iw[1];};
    auto pm = [&](size_t it){ return std::pow(1-it/(max_iter-1.),1/mu);};
    std::array<Particle<N>,S> swarm;
    for (size_t i = 0; i < S; i++)
      swarm[i]=Particle(lower_bound,upper_bound,problem);
    auto gBest = swarm[0];
    for (size_t i = 0; i < max_iter; i++) {
      if (auto tmp=Particle<N>::get_Best(swarm); tmp.dominates(gBest))
        gBest=tmp;
      auto wc = w(i);
      auto pc = pm(i);
      for (size_t j = 0; j < S; j++) {
        swarm[j].update(gBest,problem,wc,c,pc);
      }
    }
    return std::make_pair(gBest,swarm);
  }
} /* pso */
#endif //PSO_H
