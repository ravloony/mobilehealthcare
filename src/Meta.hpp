#ifndef META_H
#define META_H

#include <math.h>

#include "Route.hpp"
#include "Init.hpp"
#include "Solution.hpp"
#include "DeletionOperators/Delete.hpp"
#include "Output/Statistics.hpp"

class Meta
{
  private:
    Init* _init;
    vector<Delete*> _deleters;
    vector<Init*> _inserters;
    Solution _solution;
    DataImporter* _data_importer;
    vector<Request*> _request_pool;
    Solution _best_solution;
    Statistics _stat;
  public:
    Meta();
    Meta(DataImporter* d, Init* init);
    ~Meta();
    void apply_init();
    void apply_main();
    Solution& get_solution();
    void display_solution();
    double get_move_prob(Solution& currentSol, Solution& newSol, double temp);
    void add_deleter(Delete* del);
    void add_inserter(Init* ins);
    Statistics& get_stat();
};

#endif // META_H
