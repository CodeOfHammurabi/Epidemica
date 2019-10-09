/*Biome Types
	1. Plains: weak to Anthrax, Bubonic Plague; resistant to Tuberculosis
	2. Mountains: weak to Tuberculosis, Anthrax; resistant to Cholera 
	3. Forests: weak to Tuberculosis, Bubonic Plague; resistant to Anthrax
	4. DPM: weak to Bubonic Plague, Cholera; resistant to Anthrax
	5. Coasts: weak to Cholera, Anthrax; resistant to Bubonic Plague
	6. Islands: weak to Cholera, Tuberculosis; resistant to Bubonic Plague
	Select one of 4 diseases-> each is strong in certain regions (if we cannot model real world diseases through use of SIR model/PDEs, create your own diseases!)
	1. Anthrax
	2. Cholera
	3. Tuberculosis
	4. Bubonic Plague
	Continents
	1. Asia
      - Plains: Gangetic Plains
      - Mountains: Pamir Knot
      - Forests: Borneo
      - Deserts, Plateaux, and Mesas: Karakum
      - Coasts: Indian Peninsula
      - Islands: Indonesian Archipelago
 	2. Africa
      - Plains: Serengeti and Okavango Deltas
      - Mountains: Kilimanjaro
      - Forests: Congo Rainforest
      - Deserts, Plateaux, and Mesas: Sahara
      - Coasts: Bight of Benin, Horn of Africa, Gulf of Africa
      - Islands: Madagascar
	3. South America
      - Plains: Pampas, Pantanal
      - Mountains: Andes
      - Forests: Amazon
      - Deserts, Plateaux, and Mesas: Atacama
      - Coasts: Humboldt Current Region
      - Islands: Galapagos, Easter and Falkland
	4. North America
      - Plains: Prairie
      - Mountains: Rockies
      - Forests: Central American Rainforest
      - Deserts, Plateaux, and Mesas: Mojave
      - Coasts: Western and Eastern Seaboard
      - Islands: Aleutians, Hawaii, Caribbean
	5. Oceania
      - Plains: Canterbury
      - Mountains: South Alps
      - Forests: Papua New Guinea
      - Deserts, Plateaux, and Mesas: Great Victoria Desert
      - Coasts: Great Barrier Reef
      - Islands: South Pacific
	6. Europe
      - Plains: Steppes
      - Mountains: Alps
      - Forests: Taiga
      - Deserts, Plateaux, and Mesas: Scandinavia
      - Coasts: Baltic Coast
	- Islands: Greenland, Spanish Islands*/
#include<iostream>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<cstring>
/*Now, the list of continental bonuses- what benefit do you get for starting on a continent? (This bonus remains constant throughout the game; does not change when you shift continents)
1. Africa: At the beginning of the game, there is a  15% chance that the BCR will decrease by 1.
2. Asia: At each mutation, there is a 25% chance that you will get an extra mutation.
3. Europe (Challenge Mode): BER decreases by 5 each time you receive a mutation.
4. Oceania: There is a 15% chance that all biome resistances are neglected.
5. North America: At each colonization of a new biome, there is a 5% chance that you will colonize another region. 
6. South America: If BER becomes zero, there is a 25% chance that you will be revived ONCE with a BER of 10.*/
//continental bonuses: insert into appropriate places, will add appropriate parameters later
using namespace std;
class place
{
	public:
	int biometype,continent,BCR,cqr,contcqr; //cqr checks if the biome in question has been owned or not
	char name[50],contname[15],btype[30];
	place()
	{
		cqr=0;
		contcqr=0;
	}
}Biome[6][6];
class microbe
{
	public:
	char mname[20];
	int BER,BMR,continenti, ncqr,disease; 
	microbe()
	{
		BER=150;
		ncqr=0;
		BMR=5;
	}
void countdn(int ct[], microbe m);

}mcrb;
int ct[2];
int baseBCR;
int assignbcr(microbe mcrb,place p)
{
		int BCR=6;
		if(mcrb.BER==150)
		switch (p.biometype)
		{
			case 1:if(mcrb.disease==1||mcrb.disease==4)
			       BCR--;
				else if(mcrb.disease==3)
				{			
					BCR++;
				}
				break;
			case 2:if(mcrb.disease==3||mcrb.disease==1)
			       BCR--;
				else if(mcrb.disease==2)
				{		
					BCR++;
				}
				break;
			case 3:if(mcrb.disease==3||mcrb.disease==4)
			       BCR--;
				else if(mcrb.disease==1)
				{	
					BCR++;
				}
				break;
			case 4:if(mcrb.disease==2||mcrb.disease==4)
			       BCR--;
				else if(mcrb.disease==1)
				{			
					BCR++;
				}
				break;
			case 5:if(mcrb.disease==1||mcrb.disease==2)
			       BCR--;
				else if(mcrb.disease==4)
				{				
					BCR++;
				}
				break;
			case 6:if(mcrb.disease==2||mcrb.disease==3)
			       BCR--;
				else if(mcrb.disease==4)
				{				
					BCR++;
				}
				break;
			default://Lol srsly?
				break;
		}
		if(mcrb.ncqr>20&&mcrb.ncqr<=30)
		BCR++;
		else if(mcrb.ncqr>30)
		BCR+=2;
		if(BCR<=3)
		BCR=3;
		return BCR;
}
void gotoneigh(int ct[],microbe mcrb,place Biome[6][6])//p=Biome[ct[0]],p[]=Biome[ct[0]][]
	{
		if(mcrb.ncqr==36)
		{
			cout<<"YOU DA REAL SCOURGE OF HUMANKIND!"<<endl<<"CONGRATULATIONS, you have conquered the WORLD!"<<endl<<endl;
			cout<<"No. of Biomes conquered - "<<mcrb.ncqr;
			exit(0);
		}
		int b;
		st:	
		srand(time(NULL));	
		b=(rand()%6); 		
		if(Biome[ct[0]][b].cqr==0)
		{
			ct[1]=b;

			Biome[ct[0]][b].BCR=assignbcr(mcrb,Biome[ct[0]][b]);
		}
		else
		{
			int chkemp=0;
			for(int i=0;i<6;i++)
			{
				if(Biome[ct[0]][i].cqr==0)
				chkemp=1;
			}
			if(chkemp==1)
			goto st;
			else if(chkemp==0)
			{
				cout<<endl<<Biome[ct[0]][ct[1]].contname<<" CONQUERED!";
				for(int i=0;i<6;i++)
				{
					Biome[ct[0]][i].contcqr=1;	
				}
				tt:
				srand(time(NULL));
				ct[0]=rand()%6;
				if(Biome[ct[0]][b].contcqr==0)
				{
					if(Biome[ct[0]][b].cqr==0)
					{
						ct[1]=b;
						Biome[ct[0]][b].BCR=assignbcr(mcrb,Biome[ct[0]][b]);
					}
					else
					{
						int chkemp1=0;
						for(int i=0;i<6;i++)
						{
							if(Biome[ct[0]][b].cqr==0)
							chkemp1=1;
						}
						if(chkemp1==1)
						goto st;
						else
						{
							cout<<"Continent Already CONQUERED!";
							goto tt;
						}
						int chkempc=0;
						for(int i=0;i<6;i++)
						{
							if(Biome[i][1].contcqr==0)
							chkempc=1;
						}
						if(chkempc==1)
						goto tt;	
						else if(chkempc==0)
						{	
							cout<<"YOU DA REAL SCOURGE OF HUMANKIND!"<<endl<<"CONGRATULATIONS, you have conquered the WORLD!";
							exit(0);
						}
					}
				}
			}
			//gotta think of intercontinental migration
		}
	}
void microbe::countdn(int ct[], microbe mcrb)
{
	int lowestRate = 3;
	int mutaratemp;
	int BER_rise_min = 5;
	int BER_rise_max = 15;
	int BER_rise;
	int highestRate = 8;
	int mutarate;
	int mutanum;
	int mutafirst = 1;
	int BER_fall;
	int mutalast = 10;
	string mutaname;//add BCR as parameter
	while(mcrb.BER>0)
	{
		srand (time (NULL));
		mutarate = rand () % ((highestRate - lowestRate) + 1) + lowestRate;
		mutaratemp=mutarate;
		for (int i = mutarate; i > 0&&mcrb.BER!=0; i--)
		{
			cout <<endl<< "You will receive a mutation in " << mutarate << " turns." <<endl;
			--mutarate;
			Biome[ct[0]][ct[1]].BCR--;
			cout <<endl<<" Turns left for biome colonization is now " << Biome[ct[0]][ct[1]].BCR << ". "<<endl;
			cout<<"You now have "<<--mcrb.BER<<" turns left before eradication."<<endl;
			if(mcrb.BER==0)
			{
				cout<<endl<<"You have been ERADICATED"<<endl<<endl;
				cout<<"No. of Biomes conquered - "<<mcrb.ncqr;
				exit(0);
			}
			if(Biome[ct[0]][ct[1]].BCR<=0)
			{
				mcrb.ncqr++;
				cout<<endl<<Biome[ct[0]][ct[1]].name<<" CONQUERED";
				cout<<endl<<"No. of Biomes conquered - "<<mcrb.ncqr;			
				Biome[ct[0]][ct[1]].cqr=1;
				gotoneigh(ct,mcrb,Biome);
				cout<<endl<<"Arrived at "<<Biome[ct[0]][ct[1]].name<<" in "<<Biome[ct[0]][ct[1]].contname<<"."<<endl<<"Biome Type - "<<Biome[ct[0]][ct[1]].btype;
			}
			sleep (1);
		}
		if (mutarate == 0&&mcrb.BER!=0)
		{
			mutanum = rand () % ((mutalast - mutafirst) + 1) + mutafirst;
			cout <<endl<< "You have received a new mutation! It is mutation number " <<mutanum << ". "<<endl;
			switch (mutanum)
			{
				case 1:
				mutaname = "Favoured spread";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the base country colonization rate decreases by 1. "<<endl;
				baseBCR = 4;
				break;
				case 2:
				mutaname = "Impeded spread";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the base country colonization rate increases by 1. "<<endl;
				baseBCR = 6;
				break;
				case 3:
				mutaname = "Strain Evolution";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the the number of turns left before Eradication increases between 5 and 15."<<endl;;
				BER_rise = rand () % ((BER_rise_max - BER_rise_min) + 1) + BER_rise_min;
				mcrb.BER = mcrb.BER + BER_rise;
				cout << "The new rate of eradication is: " << mcrb.BER << ". "<<endl;
				break;
				case 4:
				mutaname = "Strain Extinction";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the number of turns left before eradication decreases by a number between 1 and 5."<<endl;
				BER_fall = rand () % ((5 - 1) + 1) + 1;
				mcrb.BER = mcrb.BER - BER_fall;
				cout << "The new rate of eradication is: " << mcrb.BER << ". "<<endl;
				break;
				case 5:
				mutaname = "Severe Symptoms";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the number of turns left before mutation decreases by 1 on either side."<<endl;
				highestRate = highestRate - 1;
				lowestRate = lowestRate - 1;
				break;
				case 6:
				mutaname = "Weakening Symptoms";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the number of turns left before mutation increases by 1 on either end."<<endl;
				highestRate = highestRate + 1;
				lowestRate = lowestRate + 1;
				break;
				case 7:
				mutaname = "Antibiotic Resistance";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the BER increases by 10 percent ";
				cout<<", but Mutation Number 3, Strain Evolution, will increase BER only from 2 to 12. "<<endl;
				BER_rise_min=2;
				BER_rise_max=12;
				mcrb.BER=1.1*mcrb.BER;
				cout<<"You now have "<<mcrb.BER<<" turns left before eradication."<<endl;
				break;
				case 8:
				mutaname = "Medical R&D";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the BER decreases by 10 percent, but Mutation Number 3, Strain Evolution, will increase BER only from 7 to 17. "<<endl;
				BER_rise_min=7;
				BER_rise_max=17;
				mcrb.BER=0.9*mcrb.BER;
				cout<<"You now have "<<mcrb.BER<<" turns left before eradication."<<endl;
				break;
				/*case 9:
				mutaname="Colonization!";
				cout<<"It is the mutation of "<<mutaname<<" Its effect is that you spread to a new continent, where you get a random biome."<<endl;
				srand(time(NULL));
				ct[0]=rand()%6;
				gotoneigh(ct,mcrb,Biome[ct[0]]);
				break;*/
				default:
				cout<<"Oops, sorry! You did not receive a mutation this time. Maybe you will evolve next time! "<<endl;
			}
			
			sleep(1);
		}
	}
}	
int main()
{
	int a,b,c,d,e,cont;
	strcpy(Biome[0][0].name,"Gangetic Plains\0");
	strcpy(Biome[0][1].name,"Pamir Knot\0");
	strcpy(Biome[0][2].name,"Borneo\0");
	strcpy(Biome[0][3].name,"Karakum\0");
	strcpy(Biome[0][4].name,"Indian Peninsula\0");
	strcpy(Biome[0][5].name,"Indonesian Archipelago\0");
	strcpy(Biome[1][0].name,"Serengeti and Okavango Deltas\0");
	strcpy(Biome[1][1].name,"Kilimanjaro\0");
	strcpy(Biome[1][2].name,"Congo Rainforest\0");
	strcpy(Biome[1][3].name,"Sahara\0");
	strcpy(Biome[1][4].name,"Bight of Benin, Horn of Africa, Gulf of Africa\0");
	strcpy(Biome[1][5].name,"Madagascar\0");
	strcpy(Biome[2][0].name,"Pampas, Pantanal\0");
	strcpy(Biome[2][1].name,"Andes\0");
	strcpy(Biome[2][2].name,"Amazon\0");
	strcpy(Biome[2][3].name,"Atacama\0");
	strcpy(Biome[2][4].name,"Humboldt Current Region\0");
	strcpy(Biome[2][5].name,"Galapagos, Easter and Falkland\0");
	strcpy(Biome[3][0].name,"Prairies\0");
	strcpy(Biome[3][1].name,"Rockies\0");
	strcpy(Biome[3][2].name,"Central American Rainforest\0");
	strcpy(Biome[3][3].name,"Mojave\0");
	strcpy(Biome[3][4].name,"Eastern and Western Seaboard\0");
	strcpy(Biome[3][5].name,"Aleutians, Hawaii, Caribbean\0");	
	strcpy(Biome[4][0].name,"Canterbury\0");
	strcpy(Biome[4][1].name,"South Alps\0");		
	strcpy(Biome[4][2].name,"Papua New Guinea\0");
	strcpy(Biome[4][3].name,"Great Victoria Desert\0");
	strcpy(Biome[4][4].name,"Great Barrier Reef\0");
	strcpy(Biome[4][5].name,"South Pacific\0");
	strcpy(Biome[5][0].name,"Steppes\0");
	strcpy(Biome[5][1].name,"Alps\0");
	strcpy(Biome[5][2].name,"Taiga\0");
	strcpy(Biome[5][3].name,"Scandinavia\0");
	strcpy(Biome[5][4].name,"Baltic Coast\0");
	strcpy(Biome[5][5].name,"Spanish Islands\0");
	//continentname	
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			switch(i)
			{
				case 0:strcpy(Biome[i][j].contname,"Asia\0");
					break;
				case 1:strcpy(Biome[i][j].contname,"Africa\0");
					break;
				case 2:strcpy(Biome[i][j].contname,"South America\0");
					break;
				case 3:strcpy(Biome[i][j].contname,"North America\0");
					break;
				case 4:strcpy(Biome[i][j].contname,"Oceania\0");
					break;
				case 5:strcpy(Biome[i][j].contname,"Europe\0");
					break;
				default:break;
			}
		}
	}
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			switch(i)
			{
				case 0:strcpy(Biome[j][i].btype,"Plains\0");
					break;
				case 1:strcpy(Biome[j][i].btype,"Mountains\0");
					break;
				case 2:strcpy(Biome[j][i].btype,"Forests\0");
					break;
				case 3:strcpy(Biome[j][i].btype,"Deserts, Plateaux, Mesas\0");
					break;
				case 4:strcpy(Biome[j][i].btype,"Coast\0");
					break;
				case 5:strcpy(Biome[j][i].btype,"Islands\0");
					break;
				default:break;
			}
		}
	}
  cout<<"Welcome to Epidemica, the disease spread simulator!"<<endl;
  cout<<"Here, you play the role of a deadly disease whose sole purpose is to cleanse the world!"<<endl;
  cout<<"From what?"<<endl;
  cout<<"Deep down you know the answer!"<<endl;
  cout<<"HUMANS!"<<endl;
  cout<<"Before we begin the assault, let us have some formalities brushed aside."<<endl;
  cout<<"What is your name, dear friend?"<<endl;
  string player_name;
  getline(cin, player_name);
  cout<<"Well, welcome, "<<player_name<<"!"<<endl;
  cout<<"In a short while, we will be a deadly disease and we will be infecting our first human!"<< endl;
  cout<<"What's your goal in this 'Madness'?"<<endl;
  cout<<"Are you inspired by Thanos to slay half of all life for the good life itself?"<< endl;
  cout<<"Or are you a purist disease seeking to cleanse planet Earth of its most widespread disease."<<endl;
  cout<<"Deep down you know the answer!"<<endl;
  cout<<"FILTHY HUMANS?"<<endl;
  cout<<"Ah, but is your real motive simply the base desire of you surviving the longest while others simply 'perish'?"<<endl;
  cout<<"Or you just want to kill some humans!"<<endl;
  cout<<"A LOT of them"<<endl;
  cout<<"Whatever your motives are, we don't judge."<<endl;
  cout<<"Do know that humanity will not be an easy foe; they will fight back, and will fight hard, real hard!"<< endl;
  cout<<"With this said, let's get you your weapon!"<<endl;
  cout<<"Now, my beloved plague-mongerer, "<<player_name<<", it's time to select your Weapon, a.k.a. disease."<<endl;
  cout<<"Your choices shall appear any moment now."<<endl;
  cout<<"A word of caution my friend, these are some of the most virulent things to hit humanity"<<endl;
  cout<<"Both in the past, the present and possibly in the future: "<<endl;
  cout<<"Every disease has a 'Homeground' or its Locale. This is where it is the strongest."<<endl;
  cout<<"There are places where this disease is useless!"<<endl;
  cout<<"Keep this in your mind and proceed with the game!"<<endl;
  cout<<"When you are prompted to enter the name of your weapon, enter a number from 1 to 4."<<endl;
  cout<<"Remember, each disease is number coded."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>d;
  cout<<"ANTHRAX"<<endl;
  cout<<"Caused by Bacillus anthracis, Anthrax have spores that can live for a long, long time."<< endl;
  cout<<"Its symptoms include high fever, fatigue, flu-like symptoms, shock, and in later stages, meningitis. "<<endl;
  cout<<"A recent developments in biowarfare created inhalatory anthrax, the most dangerous form of anthrax you can get."<<endl;
  cout<<"Anthrax is strong in Coasts, Mountains, and Plains Biomes, but is weak in Forests and Desert-Plateau-Mesa Biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>a;
  cout<<"CHOLERA."<<endl;
  cout<<"Caused by the bacterium Vibrio cholerae, Cholera is spread through contaminated water."<<endl;
  cout<<"The rampant pollution of drinking water sources has led to cholera being a highly communicable disease."<<endl;
  cout<<"Its symptoms include diarrhoea, dehydration, vomiting and cramps."<<endl;
  cout<<"Cholera is strong in Desert-Plateau-Mesa, Coasts, and Island Biomes, but is weak in Mountain biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>b;
  cout<<"TUBERCULOSIS."<<endl;
  cout<<"Caused by the bacterium Mycobacterium tuberculosis, tuberculosis, a.k.a. consumption, phthisis or just TB, is a deadly disease that spreads via air."<<endl;
  cout<<"Increasing population presents a problem in maintaining people at a 'safe' distance."<<endl;
  cout<<"This could be a jackpot!"<<endl;
  cout<<"Tuberculosis is strong in Mountains, Forests, and Island biomes, but is weak in Plains biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>c;
  cout<<"Bubonic Plague. The only disease that does not need bold case."<<endl;
  cout<<"Caused by the bacterium Yersinia pestis, mainly spreads through the bite of an infected flea."<<endl;
  cout<<"Proliferation of rats in urban areas, and their fleas has brought about a rise of bubonic plague cases."<<endl;
  cout<<"It can also spread through direct contact with the infected body tissue or bodily fluids."<<endl;
  cout<<"Its symptoms include buboes (lymphnode swellings), flu-like symptoms, chills, headaches, and fatigue."<<endl;
  cout<<"Bubonic Plague is strong in Plains, Forests and Desert-Plateau-Mesa biomes, but is weak in Coasts and Island biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>e;
  cout<<"ANTHRAX : 1"<<endl;
  cout<<"CHOLERA : 2"<<endl;
  cout<<"TUBERCULOSIS : 3"<<endl;
  cout<<"Bubonic Plague : 4"<<endl;
  cout<<"Hope you have made a choice!"<<endl;
  label:
  cout<<"Now, dear "<<player_name<<", which disease would you like?"<<endl;
  int disease_choice;
  string disease_name;
  cin>>disease_choice;
  switch(disease_choice)
   {
        case 1:
            disease_name="Anthrax";
            cout<<"You have chosen Anthrax! Good choice!";
            break;
        case 2:
            disease_name="Cholera";
            cout<<"You have chosen Cholera! Good choice!";
            break;
        case 3:
            disease_name="Tuberculosis";
            cout<<"You have chosen Tuberculosis! Good choice! ";
            break;
        case 4:
            disease_name="Bubonic Plague";
            cout<<"You have chosen Bubonic Plague! Good choice! ";
            break;
        default:
            cout<<"Having second thoughts, "<<player_name<<"? Try chosing your weapon from the catalogue again?";
            goto label;
   }
	cout<<endl<<"Choose a continent"<<endl<<"1.Asia"<<endl<<"2.Africa"<<endl<<"3.South America"<<endl<<"4.North America"<<endl<<"5.Oceania"<<endl<<"6.Europe"<<endl;
	cin>>cont;
	srand(time(NULL));
	int bmi=rand()%6;
	ct[0]=cont-1;
	ct[1]=bmi;
	mcrb.disease=disease_choice;
	Biome[ct[0]][ct[1]].BCR=assignbcr(mcrb,Biome[ct[0]][ct[1]]);
	cout<<"Starting at "<<Biome[ct[0]][ct[1]].name<<" in "<<Biome[ct[0]][ct[1]].contname<<endl<<"Biome Type - "<<Biome[ct[0]][ct[1]].btype;
	mcrb.countdn(ct,mcrb);
    sleep(1);
	
	for(int i=0;i<36;i++)
	{
		Biome[i][0].biometype=((i+1)%6)+1;
		Biome[i][0].continent=(i/6)+1;
	}	
	return 0;
}
