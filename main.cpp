#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <iterator>
using namespace std;
    typedef struct Trade{
        int Date;
           string currency;
        string exchange;
        float low;
        float high;
        long long int daily_caps;
    } trade;



    bool compare1 (const trade* t1,const trade* t2){
        if (t1->Date != t2->Date){
            return t1->Date < t2->Date;
        }
        else if(t1->currency != t2->currency){
            return t1->currency < t2->currency;
        }
        else if(t1->exchange != t2->exchange){
            return t1->exchange < t2->exchange;
        }
        else
            return false;
    }


    bool compare2 (const trade *t1,const trade *t2){
        if (t1->Date != t2->Date){
            return t1-> Date < t2-> Date;
        }
        else if(t1->exchange != t2->exchange){
            return t1->exchange < t2->exchange;
        }
        else
            return false;

    }
    bool compare3 (const trade* t1,const trade* t2){
        if (t1->Date != t2->Date){
            return t1->Date < t2->Date;
        }
        else if(t1->currency != t2->currency){
            return t1->currency < t2->currency;
        }
        else
            return false;
    }

    int main(int argc,char *argv[]){

        vector <trade> t;
        vector <trade*> torder1;
        vector <trade*> torder2;
        vector<trade*>::iterator ite;
        pair<vector<trade*>::iterator,vector<trade*>::iterator> bounds;
        t.reserve(3000000);
        ifstream ifile;
        ifile.open(argv[1], ios::in);
        int inputlength=0;
        trade tmp;
            while(ifile>>tmp.Date){
                ifile>> tmp.currency>> tmp.exchange>> tmp.low>> tmp.high>> tmp.daily_caps;
                t.push_back(tmp);
                inputlength++;
                }

            ifile.close();
        torder1.reserve(inputlength);
        torder2.reserve(inputlength);
for(int i=0;i<inputlength;i++){
        torder1.push_back(&t[i]);
        torder2.push_back(&t[i]);
}

        stable_sort(torder1.begin(), torder1.end(), compare1);
        stable_sort(torder2.begin(), torder2.end(), compare2);

        string input;

        trade a;

        while(cin>>input){
            if(input == "query"){

                cin>>a.Date>>a.currency>>a.exchange;
                bounds = equal_range(torder1.begin(),torder1.end(),&a,compare1);
                if(bounds.first != bounds.second){
                    for(ite=bounds.first; ite != bounds.second ; ite++){
                        printf("%.4f ",((*ite) -> low));
                        printf("%.4f ",((*ite) -> high));
                        printf("%lld\n",((*ite) ->daily_caps));
                    }
                }
                else
                    printf("none\n");
            }

            if(input == "price"){
                string min_or_max;

                float minlow;
                float maxhigh;
                cin>>min_or_max;
                cin>>a.Date>>a.currency;

                bounds=equal_range(torder1.begin(),torder1.end(),&a,compare3);

                if(bounds.first!=bounds.second){
                    if(min_or_max == "min"){
                        ite=bounds.first;
                        minlow= ((*ite)->low);
                        for(ite=bounds.first;ite!=bounds.second;ite++){
                            if(minlow>(*ite)->low){
                                minlow=((*ite)->low);
                            }
                        }
                        printf("%.4f\n",minlow);
                    }

                    else if(min_or_max == "max"){
                        ite=bounds.first;
                        maxhigh= ((*ite)->high);
                        for(ite=bounds.first;ite!=bounds.second;ite++){
                            if(maxhigh<(*ite)->high){
                                maxhigh=((*ite)->high);
                            }
                        }
                        printf("%.4f\n",maxhigh);
                    }

                }
                   else
                    printf("none\n");
            }

            if(input == "cap"){

                long long int total_cap = 0;
                cin>>a.Date>>a.exchange;
                bounds = equal_range(torder2.begin(),torder2.end(),&a,compare2);
                if(bounds.first != bounds.second){
                    for(ite=bounds.first;ite!=bounds.second;ite++){
                        total_cap += ((*ite)->daily_caps);

                    }
                    printf("%lld\n",total_cap);
                }
                else
                    printf("none\n");
            }
            if(input =="end"){
                exit(0);
            }
        }




        return 0;


    }
