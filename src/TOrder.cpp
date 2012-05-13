#include "PodgladPostepu.hpp"
#include "Subject.hpp"
#include "Plan.h"
#include "Observer.hpp"
#include "CzasWykonania.h"
#include "ZarzadcaZadan.hpp"
#include "EvolFunctions.hpp"

using namespace evol;

int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        std::cout << "Usage: " << argv[0] << " fileWithTasks" << std::endl;
        return -1;
    }

    ZarzadcaZadan::getInstance( argv[1] );
    CzasWykonania goal(120);
    SubjectPtr realizacja( (Subject*) new Plan() );
    realizacja->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, realizacja, 1000, 0.2, 2.0 );
    populacja.registerObserver( NObserverPtr( new PodgladPostepu() ) );

    Plan *wynik;
    try
    {
        wynik = EvolFunctions::ptr_cast< SubjectPtr, Plan >(populacja.start( ));
    }
    catch ( OutOfBoundException &e )
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "\n\nNajlepszy wynik " << std::endl;
    wynik->print();
    return 0;
}
