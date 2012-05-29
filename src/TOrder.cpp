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
    std::cerr  << "<tr><td>";
    std::cerr  << ZarzadcaZadan::getInstance().getIloscMaszyn() << "</td><td>";
    std::cerr  << ZarzadcaZadan::getInstance().getIloscZadan()  << "</td><td>";
    std::cerr  << ((CzasWykonania*)&*populacja.getCurrentBestFF())->getTimeTotal() << "</td><td>";
    std::cerr  << argv[2] << "</td><td>"; //reference result
    std::cerr  << argv[3] << "</td><td>"; //population size
    std::cerr  << argv[4] << "</td><td>"; //mutateFactor
    std::cerr  << argv[5] << "</td><td>"; //crossFactor
    std::cerr  << podgladP->getLastBetter() << "</td><td>";
    std::cerr  << podgladP->getGenerationNumber() << "</td><td>";
    std::cerr  << podgladP->getTimeTaken() << "s.</td><td>";
    std::cerr  << "<a href=\"../" << argv[1] << "\">" << argv[1] << "</a></td></tr>";
    return 0;
}
