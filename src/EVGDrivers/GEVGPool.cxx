//____________________________________________________________________________
/*!

\class   driver::GEVGPool

\brief   A pool of GEVGDriver objects with an initial state key

\author  Costas Andreopoulos <C.V.Andreopoulos@rl.ac.uk>
         CCLRC, Rutherford Appleton Laboratory

\created May 24, 2005

*/
//____________________________________________________________________________

#include "EVGDrivers/GEVGDriver.h"
#include "EVGDrivers/GEVGPool.h"
#include "Interaction/InitialState.h"
#include "Messenger/Messenger.h"

using std::endl;
using namespace genie;

//____________________________________________________________________________
namespace genie {
 ostream & operator << (ostream & stream, const GEVGPool & pool)
 {
   pool.Print(stream);
   return stream;
 }
}
//___________________________________________________________________________
GEVGPool::GEVGPool() :
map<string, GEVGDriver *>()
{

}
//___________________________________________________________________________
GEVGPool::~GEVGPool()
{
  GEVGPool::const_iterator giter;
  for(giter = this->begin(); giter != this->end(); ++giter) {
    GEVGDriver * driver = giter->second;
    delete driver;
    driver = 0;
  }
}
//___________________________________________________________________________
GEVGDriver * GEVGPool::FindDriver(const InitialState & init) const
{
  string str_init = init.AsString();

  return this->FindDriver(str_init);
}
//___________________________________________________________________________
GEVGDriver * GEVGPool::FindDriver(string init) const
{
  GEVGDriver * driver = 0;

  if ( this->count(init) == 1 ) {
    GEVGPool::const_iterator giter = this->find(init);
    driver = giter->second;
  } else {
     LOG("GEVGPool", pWARN)
            << "No GEVGDriver object for init-state: " << init << " in pool";
  }
  return driver;
}
//___________________________________________________________________________
void GEVGPool::Print(ostream & stream) const
{
  stream << "\n GEVGDriver List:" << endl;

  GEVGPool::const_iterator giter;

  for(giter = this->begin(); giter != this->end(); ++giter) {

    string  init_state  = giter->first;
    GEVGDriver * driver = giter->second;

    stream << "\n[" << init_state << "]";
    stream << *driver;
  }
}
//___________________________________________________________________________

