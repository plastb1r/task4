#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

char* names[2][9] = {{"Рудольф", "Стремительный", "Танцор", "Скакун",
    "Резвый", "Комета", "Купидон", "Гром", "Молния"},
    {"Рудольф, пьяная скотина, опять пришёл нажравшись. Бедные дети думают, что у него красный нос потому, что он волшебный.",
        "Неожиданно прибежал Стремительный. О! Кажется он сегодня ничего не принял. А нет, показалось. Опять на спидах.",
        "Вы когда-нибудь видели постоянно танцующего оленя? А я сейчас вижу оленя-Танцора\n Что? В психушку? Я бы с радостью, \
но ни одна психушка не соглашатеся забрать меня из этого дурдома.",
        "Ну хоть один нормальный олень! Кхм. Кхм.\n Скакун прискакал к Санте",
        "О! Резвый бежит. Наверное опять ничего не случилось.",
        "Хм. Падающая звезда? Или нет... Господи боже ж ты мой! Сколько ему раз говорили не летать без Санты. Он же совершенно не умеет приземлятья!!!\n \
БДЫЩЩЩ!!! Когда-нибудь Комета уничтожит нас, как динозвров.",
        "Самое время подойти Купидону, но почему-то здесь опять стоит целое, чёрт побери, стадо олених.\n Хотя, нет всё впорядке.\
Он вооон там занимается че... Кхм. Лучше бы я этого не видел.",
        "Пригромыхал Гром. Когда-нибудь я так оглохну. Нет, серьёзно, он один создаёт больше шума, чем целое стадо",
        "Молния. Кто-нибудь скажете ему, что покрывать всего себя какой-то липкой светоотражающей жидкостью - плохая идея."}};
int global[6] = {0, 9, 20, 7, 30, 60};
    /* 
     * Первая переменная - выключатель
     * 2-5 - N, M, K и T соответственно
     * Последня - время работы
     */
int status[3] = {1, 0, 0};
    /*
     * Первая таймер 
     * Вторая кол-во оленей у порога
     * Третья эльфов
     */
int elf[100];
int rndrs[9];
    
void *Santa(), *Elves(), *Reindeers(), *Events();

int main(int argc, char* argv[])
{
    srand(time(0));
    
    pthread_t tid1, tid2, tid3, tid4;
    setlocale(LC_ALL, "ru_RU.utf8");
    
    for(int i = 1; i< argc; i++)
    {
        switch(argv[i][0])
        {
            case 'G':
            case 'g': global[0] = 1;
                    fprintf( stderr, " 0     0\n``` ~ ```\n\n  S-S-SENPAI...\n YOU WANT TO PLAY WITH ME\n");
                    break;
            case 'n':
            case 'N': argv[i][0]='+';
                    if( atoi(argv[i]) > 7)
                    {
                        fprintf(stderr,"ERROR 404: Не найдено необходимое количество оленей\n");
                    }
                    else
                    {
                        global[1] = atoi(argv[i]);
                    };
                    break;
            case 'm':
            case 'M': argv[i][0]='+';
                    global[2] = atoi(argv[i]);
                    break;
            case 'k':
            case 'K': argv[i][0]='+';
                    global[3] = atoi(argv[i]);
                    break;
            case 't':
            case 'T': argv[i][0]='+';
                    global[4] = atoi(argv[i]);
                    break;
            case 'w':
            case 'W': argv[i][0]='+';
                    if( atoi(argv[i]) == 418)
                    {
                        fprintf(stderr,"ERROR 418: I'm a teapot\n");
                        global[0] = 1;
                    };
                    global[5] = atoi(argv[i]);
                    break;
        }
    }
    int elf[global[2]];
    for(int i = 0; i < global[2]; i++)
        elf[i] = rand()%100;
    int rndrs[global[1]];
    for(int i = 0; i < global[1]; i++)
        rndrs[i] = rand()%100;
    
    pthread_create( &tid1, NULL, Reindeers, NULL);
    pthread_create( &tid2, NULL, Elves, NULL);
    pthread_create( &tid3, NULL, Santa, NULL);
    
    status[0]=0;
    for( global[5]; global[5]>0; global[5]--)
        sleep(1);
    
    pthread_join( tid3, NULL);
    pthread_join( tid2, NULL);
    pthread_join( tid1, NULL);
}

void *Reindeers()
{
    while(status[0])
        sleep(1);
    
    for(int i = 0; i < global[1]; i++)
        rndrs[i] = rand()%100;
    
    while(global[5] > 0)
    {
        for(int i = 0; i < global[1]; i++)
        {
            if(rndrs[i]>0)
                rndrs[i]--;
            if(rndrs[i]==0)
            {
                char buff[13];
                time_t t = time(NULL);
                strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
                if(global[0])
                {
                    printf("%s: %s\n", buff, names[1][i]);
                }
                else
                {
                    printf("%s: %s пришёл к Сатане\n", buff, names[0][i]);
                }
                status[1]++;
                rndrs[i]--;
            }
        }
        sleep(1);
    }
}

void *Elves()
{
    while(status[0])
        sleep(1);
    
    for(int i = 0; i < global[2]; i++)
        elf[i] = rand()%100;
    
    while(global[5] > 0)
    {
        for(int i = 0; i < global[2]; i++)
        {
            if(elf[i]>0)
                elf[i]--;
            if(elf[i]==0)
            {
                char buff[13];
                time_t t = time(NULL);
                strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
                printf("%s: Эльф под номером %i подошёл к двери\n", buff, i);
                status[2]+=1;
                elf[i]--;
            }
        }
        sleep(1);
    }
}

void *Santa()
{
    void beer()
    {
        if( status[1] == global[1])
        {
            char buff[13];
            time_t t = time(NULL);
            strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
            printf("%s: Сатана запрягает оленей и везёт детям бухлишко\n", buff);
            sleep(rand()%30);
            t = time(NULL);
            strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
            printf("%s: Санта распрягает оленей\n", buff);
            status[1]=0;
            for(int i = 0; i < global[1]; i++)
                rndrs[i] = rand()%100;
        }
    }
    
    while(status[0])
        sleep(1);
    
    while(global[5] > 0)
    {
        if(status[2] >= global[3])
        {
            while(status[2] > 0)
            {
                int i =0;
                beer();
                while( i< global[2])
                {
                    if(elf[i] == -1)
                    {
                        char buff[13];
                        time_t t = time(NULL);
                        strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
                        elf[i]-=1;
                        printf("%s: Санта заводит эльфа под номером %i в дом\n", buff, i);
                        i++;
                        break;
                    };
                    i++;
                }
                sleep(1);
                status[2]--;
            };
            
            
            char buff[13];
            time_t t = time(NULL);
            strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
            printf("%s: Начинается совещание\n", buff);
            status[0]= global[4];
            while(status[0]>0)
            {
                status[0]--;
                sleep(1);
            };
            t = time(NULL);
            strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
            printf("%s: Совещание окончено\n", buff);
            
            
            for(int i = 0; i< global[2]; i++)
            {
                if(elf[i]== -2)
                {
                    char buff[13];
                    time_t t = time(NULL);
                    strftime(buff, sizeof buff, "%T UTC", gmtime(&t));
                    elf[i]= rand()%100;
                    printf("%s: Санта выводит эльфа под номером %i из дома\n", buff, i);
                    sleep(1);
                }
            }
        };
        beer();
    }
}           
