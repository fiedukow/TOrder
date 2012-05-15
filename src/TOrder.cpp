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
    if( argc < 4 )
    {
        std::cout << "Usage: " << argv[0] << " fileWithTasks goalValue populationSize" << std::endl;
        return -1;
    }

    ZarzadcaZadan::getInstance( argv[1] );

    CzasWykonania goal(atoi(argv[2]));
    SubjectPtr realizacja( (Subject*) new Plan() );
    realizacja->setInitialValue();
    Population populacja( ( FitnessFunction& ) goal, realizacja, atoi(argv[3]), 0.3, 2.0 );
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
