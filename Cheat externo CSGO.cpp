#include "base de tudo.h"
#include "terceiraPessoa.h"
#include "autopistol.h"
#include "bhop.h"
#include "aimbot.h"
#include "reduzir_flash.h"
#include "glow.h"
#include "triggerbot.h"
#include "musiquinha.h"


void PaginaMain()
{
    std::cout << R"(
                  __   ___   ___ ___   _____  _______ ___ ___ _  _   _   _    
                  \ \ / /_\ / __/ __| | __\ \/ /_   _| __| _ \ \| | /_\ | |   
                   \ V / _ \ (_| (__  | _| >  <  | | | _||   / .` |/ _ \| |__ 
                    \_/_/ \_\___\___| |___/_/\_\ |_| |___|_|_\_|\_/_/ \_\____|                                                                                           
        )" << std::endl;
    std::cout << "========================================================================================================================" << std::endl;
    std::cout << "             KEY BINDS                                                                                                  " << std::endl;
    std::cout << "                                                                                                                        " << std::endl;
    std::cout << "GLOW         : [NUMPAD 0]                                                                                               " << std::endl;
    std::cout << "BHOP         : [NUMPAD 1]                                                                                               " << std::endl;
    std::cout << "TRIGGER BOT  : [NUMPAD 2] hold alt                                                                                      " << std::endl;
    std::cout << "AUTO PISTOL  : [NUMPAD 3]                                                                                               " << std::endl;
    std::cout << "THIRDPERSON  : [NUMPAD 4]                                                                                               " << std::endl;
    std::cout << "REDUCE FLASH : [NUMPAD 5]                                                                                               " << std::endl;
    std::cout << "========================================================================================================================" << std::endl;
    std::cout << "              AVISOS                                                                                                    " << std::endl;
    std::cout << " 01: Reincie o programa ao trocar de mapa                                                                               " << std::endl;
    std::cout << " 02: Se o cheat nao estiver funcionando, baixe a nova versao                                                            " << std::endl;
    std::cout << " 03: As binds [NUMPAD] podem apresentar bugs, tendo que ser precionada varias vezes se necessario                       " << std::endl;
    std::cout << "========================================================================================================================" << std::endl;
    std::cout << "LOGS:" << std::endl;




    while (true)
    {
        using namespace std;
        val.flag = MemClass.readMem<BYTE>(val.localPlayer + offset.m_fFlags);

        DWORD close_entity = NULL;
        int cross_distance = -15000;

        int my_choice = 0;
        int my_circle = 30;
        float my_smooth_choice = 1;

        if (GetAsyncKeyState(VK_F7))
        {
            musiquinha();
        }

        if (GetKeyState(VK_NUMPAD0))
        {
            glow();
        }

        if (GetKeyState(VK_NUMPAD1))
        {
            bhop();
        }

        if (GetKeyState(VK_NUMPAD2))
        {
            triggerbot();
        }

        if (GetKeyState(VK_NUMPAD3))
        {
            autopistol();
        }

            thirdperson();

        if (GetKeyState(VK_NUMPAD5))
        {
            reduzirF();
        }

        if (GetKeyState(VK_NUMPAD6))
        {
            if (close_entity)
            {
                aim_bot(close_entity, my_choice, my_smooth_choice);
            }
        }

        Sleep(1);
    }
}

void clear() 
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void Inicio() 
{
    std::cout << R"(
 __   ___   ___ ___ _____   _____  _______ ___ ___ _  _   _   _            _    ___   ___ ___ _  _ 
 \ \ / /_\ / __/ __|_   _| | __\ \/ /_   _| __| _ \ \| | /_\ | |     ___  | |  / _ \ / __|_ _| \| |
  \ V / _ \ (_| (__  | |   | _| >  <  | | | _||   / .` |/ _ \| |__  |___| | |_| (_) | (_ || || .` |
   \_/_/ \_\___\___| |_|   |___/_/\_\ |_| |___|_|_\_|\_/_/ \_\____|       |____\___/ \___|___|_|\_|                                               
        )" << std::endl;

    std::cout << "senha: " << std::endl;
    float senha;
    std::cin >> senha;


        if (senha == 1911)
        {
            clear();
            PaginaMain();
        }
        else
        {
            std::cout << "SENHA INCORRETA" << std::endl;
            Beep(600, 1000);
        }

    
}

int main()
{
    
    
    int proc = MemClass.getProcess("csgo.exe");

    val.gameModule = MemClass.getModule(proc, "client.dll");
    val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offset.dwLocalPlayer);




    if (val.localPlayer == NULL)
        while (val.localPlayer == NULL)
            val.localPlayer = MemClass.readMem<DWORD>(val.gameModule + offset.dwLocalPlayer);




    Inicio();

    return 0;
}
