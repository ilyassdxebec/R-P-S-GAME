#include <iostream> 
#include <cstdlib>    
#include <ctime>    
using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo{

 short RoundNumber;
 enGameChoice PlayerChoice;
 enGameChoice ComputerChoice;
 enWinner RoundWinner;
 string RoundWinnerName;
};

struct stGameResults{   

 short TotalRounds;
 short PlayerWonTimes;
 short ComputerWonTimes;
 short DrawTimes;
 enWinner FinalWinner;
 string FinalWinnerName;
};

short DecideHowManyRounds(){
    short rounds;
   do{
    cout<<"How many rounds you want to play (1-10) ? : ";
    cin>>rounds;
   }while(rounds>10||rounds<1);
   return rounds;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enGameChoice GetPlayerChoice(){

    short Choice;
   do{
    cout<<"Your Choice: [1]:Rock, [2]:Paper, [3]:Scissors ? : ";
    cin>>Choice;
   }while(Choice>3||Choice<1);
    cout<<endl;
    return (enGameChoice)Choice;
}

enGameChoice GenerateComputerChoice(){
    return (enGameChoice)RandomNumber(1,3);
}

string ChoiceName(enGameChoice Choice){
 string ChoiceName[] = {"Rock","Paper","Scissors"};
 return ChoiceName[Choice-1];
}

void PrintRoundInfo(stRoundInfo RoundInfo){

 cout<<"_________________Round["<<RoundInfo.RoundNumber<<"]_________________"<<endl;
 cout<<"Player Choice : "<<ChoiceName(RoundInfo.PlayerChoice)<<endl;
  cout<<"Computer Choice : "<<ChoiceName(RoundInfo.ComputerChoice)<<endl;
   cout<<"Round Winner : "<<RoundInfo.RoundWinnerName<<endl;
   cout<<"____________________________________________\n";
}

void DisplayColor(enWinner Winner){

  switch (Winner)
  {
  case Player:
    system("color 2");
    break;
    case Computer:
    system("color 4");
    break;  
  default:
    system("color E");
  }
}

void PrintFinalResults(stGameResults FinalGameResults){

 cout<<"__________________________[Game Results]______________________________\n\n";
 cout<<"Game Rounds: "<<FinalGameResults.TotalRounds<<endl;
 cout<<"Player Won Times: "<<FinalGameResults.PlayerWonTimes<<endl;
 cout<<"Computer Won Times: "<<FinalGameResults.ComputerWonTimes<<endl; 
 cout<<"Draw Times: "<<FinalGameResults.DrawTimes<<endl;
 cout<<"Final Winner: "<<FinalGameResults.FinalWinnerName<<"\n\n";
 cout<<"___________________________________________________________"<<endl;

 DisplayColor(FinalGameResults.FinalWinner);
}

enWinner DecideRoundWinner(stRoundInfo RoundInfo){
    if(RoundInfo.PlayerChoice==RoundInfo.ComputerChoice) return Draw;

   if(RoundInfo.PlayerChoice==Rock && RoundInfo.ComputerChoice==Scissors) return Player;
   else if(RoundInfo.PlayerChoice==Paper && RoundInfo.ComputerChoice==Rock) return Player;
   else if(RoundInfo.PlayerChoice==Scissors && RoundInfo.ComputerChoice==Paper) return Player;
   else return Computer;

}

string WinnerName(enWinner WinnerOfRound){

 string RoundWinner[] = {"Player","Computer","Draw"};
 return RoundWinner[WinnerOfRound - 1];

}

enWinner FinalGameWinner(short PlayerWTimes,short ComputerWTimes){

  if(PlayerWTimes>ComputerWTimes) return Player;
  else if(PlayerWTimes<ComputerWTimes) return Computer;
  else return Draw;

}

stGameResults FillFinalGameResults(short TotalRounds,short PlayerWTimes,short ComputerWTimes,short DrawTimes){

  stGameResults GameResults;
  
  GameResults.TotalRounds = TotalRounds;
  GameResults.PlayerWonTimes = PlayerWTimes;
  GameResults.ComputerWonTimes = ComputerWTimes;
  GameResults.DrawTimes = DrawTimes;
  GameResults.FinalWinner = FinalGameWinner(PlayerWTimes,ComputerWTimes);
  GameResults.FinalWinnerName = WinnerName(GameResults.FinalWinner);

  return GameResults;
}
stGameResults StartGame(short RoundsNumber){

   short PlayerWonTimes=0,ComputerWonTimes=0,DrawTimes=0;
   stRoundInfo RoundInfo;

   for(int GameRound=1;GameRound<=RoundsNumber;GameRound++){
       RoundInfo.RoundNumber = GameRound;
       cout<<"Round ["<<GameRound<<"] begins: "<<endl;
       RoundInfo.PlayerChoice = GetPlayerChoice();
       RoundInfo.ComputerChoice = GenerateComputerChoice();
       RoundInfo.RoundWinner = DecideRoundWinner(RoundInfo);
       RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);
       
       if(RoundInfo.RoundWinner==Computer) ComputerWonTimes++;
       else if(RoundInfo.RoundWinner==Player) PlayerWonTimes++;
       else DrawTimes++;

       DisplayColor(RoundInfo.RoundWinner);
       PrintRoundInfo(RoundInfo);
   }
 return FillFinalGameResults(RoundsNumber,PlayerWonTimes,ComputerWonTimes,DrawTimes);

}

void ResetScreen(){

    system("cls");
        system("color 0");

}

string Tabs(short NumberOfTabs){

   string t = "";

 for(int i=1;i<=NumberOfTabs;i++){
    t=t+"\t";
 }
 return t;

}

void ShowGameOverScreen(){

 cout<<Tabs(1)<<"_________________________________________\n\n";
 cout<<Tabs(1)<<"          +++Game Over+++\n";
 cout<<Tabs(1)<<"_________________________________________\n\n";

}

void PlayGame(){

  char Choice;
  do{
    ResetScreen();
    stGameResults GameResults = StartGame(DecideHowManyRounds());
    ShowGameOverScreen();
    PrintFinalResults(GameResults);
    cout<<endl<<Tabs(2)<<"Do you want to Play again? (y/n)";
    cin>>Choice;
  }while(Choice=='Y'||Choice=='y');
}

int main()
{
    srand((unsigned)time(NULL)); 

    PlayGame();

}