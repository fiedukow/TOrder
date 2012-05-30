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
    if( argc < 7 )
    {
        std::cout << "Usage: " << argv[0] << " fileWithTasks goalValue populationSize";
        std::cout << "mutateFactor crossFactor timeLimit" << std::endl;
        return -1;
    }

    ZarzadcaZadan::getInstance( argv[1] );
    NObserverPtr podglad(new PodgladPostepu(atoi(argv[6])));
    PodgladPostepu* podgladP = (PodgladPostepu*)&*podglad; //just for current usage
    CzasWykonania goal(atoi(argv[2]));
    SubjectPtr realizacja( (Subject*) new Plan() );
    realizacja->setInitialValue();
    std::cout << atof(argv[4]) << " " << atof(argv[5]) << std::endl;
    Population populacja( ( FitnessFunction& ) goal, realizacja, 
                        atoi(argv[3]), atof(argv[4]), atof(argv[5]) );
    populacja.registerObserver( podglad );

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
    std::cout << "Otrzymano w pokoleniu #" << podgladP->getGenerationNumber() << std::endl;
    std::cout << "Czas szukania " << podgladP->getTimeTaken() << "s." << std::endl;
    return 0;
}
