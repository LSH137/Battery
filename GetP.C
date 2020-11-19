#include "Riostream.h"
#include <stdio.h>
#include <math.h>

struct DataSet
{
    double time = 0;
    double currunt = 0;
    double volt = 0;
    double energy = 0;
};

FILE* fp_battery;
FILE* fp_power;

char file_name[50];
char dir[250];

DataSet battery;

void GetP()
{
    scanf("%s", file_name);
    puts(file_name);

    auto c_v = new TCanvas("battery_Voltage:time","battery_Voltage:time",1200, 600);
    auto c_i = new TCanvas("battery_Currunt:time","battery_Currunt:time",1200, 600);
    auto c_p = new TCanvas("battery_Power:time","battery_Power:time", 1200, 600);

    TGraph* g_volt = new TGraph();
    TGraph* g_currunt = new TGraph();
    TGraph* g_power = new TGraph();

    sprintf(dir, "%s.csv", file_name);
    puts(dir);
    fp_battery = fopen64(dir, "r");

    sprintf(dir, "%s_power.csv", file_name);
    puts(dir);
    fp_power = fopen64(dir, "w");


    if(fp_battery != nullptr && fp_power != nullptr)
    {   
        printf("success to open file\n");

        while(!feof(fp_battery))
        {
            fscanf(fp_battery, "%lf,%lf,%lf", &battery.time, &battery.volt, &battery.currunt);
            //printf("battery: %lf %lf %lf\n", battery.time, battery.volt, battery.currunt);

            g_volt->SetPoint(g_volt->GetN(), battery.time, fabs(battery.volt));
            g_currunt->SetPoint(g_currunt->GetN(), battery.time, fabs(battery.currunt));
            g_power->SetPoint(g_power->GetN(), battery.time, fabs(battery.volt * battery.currunt));

            fprintf(fp_power, "%lf,%lf\n", battery.time, fabs(battery.currunt * battery.volt));
        }

        ///////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////

        //volt desgine
        sprintf(dir, "%s_volt:time", file_name);
        g_volt -> SetTitle(dir);
        g_volt -> SetMarkerColor(4);
        g_volt -> SetLineColor(2);              
        g_volt -> SetLineWidth(4);
        g_volt -> SetMarkerSize(1.0);
        g_volt -> SetMarkerStyle(34);

        //draw volt graph
        c_v->cd();
        g_volt->GetXaxis()->SetTitle("time[s]");
        g_volt->GetYaxis()->SetTitle("voltage[V]");
        g_volt->Draw("APL");

        //save graph
        sprintf(dir, "%s_volt:time.png", file_name);
        c_v->SaveAs(dir);

        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////

        //currunt desgine
        sprintf(dir, "%s_currunt:time", file_name);
        g_currunt -> SetTitle(dir);
        g_currunt -> SetMarkerColor(4);
        g_currunt -> SetLineColor(2);
        g_currunt -> SetLineWidth(4);
        g_currunt -> SetMarkerSize(1.0);
        g_currunt -> SetMarkerStyle(34);

        //draw currunt graph
        c_i->cd();
        g_currunt->GetXaxis()->SetTitle("time[s]");
        g_currunt->GetYaxis()->SetTitle("currunt[A]");
        g_currunt->Draw("APL");

        //save graph
        sprintf(dir, "%s_currunt:time.png", file_name);
        c_i->SaveAs(dir);

        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        
        //power desgine
        sprintf(dir, "%s_power:time", file_name);
        g_power -> SetTitle(dir);
        g_power -> SetMarkerColor(4);
        g_power -> SetLineColor(2);
        g_power -> SetLineWidth(4);
        g_power -> SetMarkerSize(1.0);
        g_power -> SetMarkerStyle(34);

        //draw currunt graph
        c_p->cd();
        g_power->GetXaxis()->SetTitle("time[s]");
        g_power->GetYaxis()->SetTitle("power[W]");
        g_power->Draw("APL");

        //save graph
        sprintf(dir, "%s_power:time.png", file_name);
        c_p->SaveAs(dir);

        //get total power
        battery.energy = g_power->Integral();
        printf("energy: %f [J]\n", battery.energy);

        ///////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////

        fclose(fp_battery);
        fclose(fp_power);
    }
    else
    {
        printf("error!: can't open file\n");
    }
    
}
