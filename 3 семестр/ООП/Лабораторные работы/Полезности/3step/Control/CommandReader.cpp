#include "CommandReader.h"

void CommandReader::makeField(int& x_size, int& y_size, Union union1){
    while(x_size<3 || y_size<3) {
        std::cout << "Enter field size: ";
        std::cin >> x_size;
        std::cin >> y_size;
        std::cout << '\n';
        if (x_size<3 || y_size<3)
            union1.getThirdLevel()->react1("Incorrect input", union1.getinfo(), union1.getLog(),0);
    }
    if (union1.getinfo().getConsoleT()) union1.getinfo().getConsole()->changeY(y_size);
};

void CommandReader::gameStart(GameField field, Mediator med, Union union1, Instruments instr, Player player, Factory* factory, WinConsoleControl cons){
    union1.getSecondLevel()->react1("Start", union1.getinfo(), union1.getLog(), 0);
    instr.drawEvents(field, factory);
    cons.setcursor(false, 0);
    system("cls");
    instr.drawField(field.getSizeX(), field.getSizeY(), field, cons);
    instr.changePosition(field, cons);
    char op = 'l';
    do{
        op = getch();
        instr.changePlayer(field.getPlayerX(), field.getPlayerY(), instr, field, '*', cons);
        switch (op) {
            case 'w':
            case 'W':
                med.move(0, -1, field, player, op, factory, instr, union1, cons);
                break;
            case 's':
            case 'S':
                med.move(0, 1, field, player, op, factory, instr, union1, cons);
                break;
            case 'a':
            case 'A':
                med.move(-1, 0, field, player, op, factory, instr, union1, cons);
                break;
            case 'd':
            case 'D':
                med.move(1, 0, field, player, op, factory, instr, union1, cons);
                break;
            default:
                break;
        }
        instr.showBill(player, field, cons);
        instr.changePosition(field, cons);
    }while(op != 'e');
};

void CommandReader::deleteShit(Union union1, Factory* factory){
    delete union1.getinfo().getFile();
    delete union1.getinfo().getConsole();
    delete union1.getThirdLevel();
    delete union1.getSecondLevel();
    delete union1.getFirstLevel();
    delete factory;
};

void CommandReader::readMesInfo(bool *info1){
    std::cout<<"Welcome to PGame. Please, answer some questions.\n"
               "Your answer should be 1 oder 2. 1 means <yes>, 0 means <no>\n"
               "If you enter incorrect number default value <no> will be applied\n";
    int info[5];
    std::cout<<"Would u like to print 1 log level?";
    std::cin>>info[0];
    std::cout<<"Would u like to print 2 log level?";
    std::cin>>info[1];
    std::cout<<"Would u like to print 3 log level?";
    std::cin>>info[2];
    std::cout<<"Would u like to print to file?";
    std::cin>>info[3];
    std::cout<<"Would u like to print console?";
    std::cin>>info[4];
    for (int i=0;i<5;i++){
        switch (info[i]){
            case 0:
                info1[i]=false;
                break;
            case 1:
                info1[i]=true;
                break;
            default:
                std::cout<<"[ProgramState] Input wasn't correct at all, so default <no> was set\n";
                info1[i]=false;
                break;
        }
    }
}
