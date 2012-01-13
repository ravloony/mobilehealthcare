#ifndef REQUESTCACHE_HPP
#define REQUESTCACHE_HPP

class Requestcache
{
  public:
    int routeSize;
    double minCost;
    int minPos;
    Requestcache();
    Requestcache(int rSize, double mCost, int mPos);
    ~Requestcache();
};

#endif // REQUESTCACHE_HPP
