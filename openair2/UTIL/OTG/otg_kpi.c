/*******************************************************************************

  Eurecom OpenAirInterface
  Copyright(c) 1999 - 2011 Eurecom

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Contact Information
  Openair Admin: openair_admin@eurecom.fr
  Openair Tech : openair_tech@eurecom.fr
  Forums       : http://forums.eurecom.fsr/openairinterface
  Address      : Eurecom, 2229, route des crêtes, 06560 Valbonne Sophia Antipolis, France

*******************************************************************************/

/*! \file otg_kpi.c main used funstions to compute KPIs
* \brief define KPIs to compute for performance analysis 
* \author A. Hafsaoui
* \date 2012
* \version 0.1
* \company Eurecom
* \email: openair_tech@eurecom.fr
* \note
* \warning

*/


#include"otg_kpi.h"
#include"otg_externs.h"

extern unsigned char NB_eNB_INST;
extern unsigned char NB_UE_INST;

void tx_throughput(int src, int dst, int application){
  
  otg_info->tx_throughput[src][dst][application]=((double)otg_info->tx_num_bytes[src][dst][application] *1000*8)/ (get_ctime()*1024); // unit Kbit/sec, if ctime in ms
	if (otg_info->tx_num_bytes_background[src][dst]>0)
  	otg_info->tx_throughput_background[src][dst]=((double)otg_info->tx_num_bytes_background[src][dst]*1000*8)/ (get_ctime()*1024); // unit Kbit/sec, if ctime in ms
}



void rx_goodput(int src, int dst, int application){

  otg_info->rx_goodput[src][dst][application]=((double)otg_info->rx_num_bytes[src][dst][application]*1000*8)/(get_ctime()*1024); // unit kB/sec, if ctime in ms 
if (otg_info->rx_num_bytes_background[src][dst]>0)
  otg_info->rx_goodput_background[src][dst]=((double)otg_info->rx_num_bytes_background[src][dst] *1000*8)/(get_ctime()*1024); // unit kB/sec, if ctime in ms
}




void rx_loss_rate_pkts(int src, int dst, int application){

  if (otg_info->rx_num_pkt[src][dst][application]<otg_info->tx_num_pkt[src][dst][application])
    otg_info->rx_loss_rate[src][dst][application]= 1 - ((double)otg_info->rx_num_pkt[src][dst][application]/otg_info->tx_num_pkt[src][dst][application]);
  else
    otg_info->rx_loss_rate[src][dst][application]=0;

  if (otg_info->rx_num_pkt_background[src][dst]<otg_info->tx_num_pkt_background[src][dst])
    otg_info->rx_loss_rate_background[src][dst]= 1 - ((double)otg_info->rx_num_pkt_background[src][dst]/otg_info->tx_num_pkt_background[src][dst]);
  else
    otg_info->rx_loss_rate_background[src][dst]=0;
  
if (otg_info->rx_loss_rate[src][dst][application]>0)
LOG_I(OTG, "LOSS_RATE (src=%d, dst=%d, appli %d ):: = %lf(pkts) [TX %d] [RX %d], [NB UL %d] [NB DL %d]\n",src, dst, application, otg_info->rx_loss_rate[src][dst][application], otg_info->tx_num_pkt[src][dst][application],otg_info->rx_num_pkt[src][dst][application],otg_info->nb_loss_pkts_ul[src][dst][application], otg_info->nb_loss_pkts_dl[src][dst][application]);


}


void rx_loss_rate_bytes(int src, int dst, int application){

  if (otg_info->rx_num_pkt[src][dst][application]<otg_info->tx_num_pkt[src][dst][application])
    otg_info->rx_loss_rate[src][dst][application]= 1 - ((double)otg_info->rx_num_bytes[src][dst][application]/otg_info->tx_num_bytes[src][dst][application]);
  else
    otg_info->rx_loss_rate[src][dst][application]=0;
  LOG_I(OTG, "loss rate (src=%d, dst=%d, appli %d ):: = %lf(bytes) \n",src, dst, application, otg_info->rx_loss_rate[src][dst][application]);

}

void nb_loss_pkts(){
unsigned int i,j,k;

otg_info->total_loss_dl=0;
otg_info->total_loss_ul=0;

  for (i=0; i<(NB_eNB_INST + NB_UE_INST); i++){
    for (j=0; j<(NB_eNB_INST + NB_UE_INST); j++){
  		for (k=0; k<MAX_EMU_TRAFFIC; k++){
 				if (i<NB_eNB_INST)
					otg_info->total_loss_dl+=(otg_info->nb_loss_pkts_dl[i][j][k] + otg_info->nb_loss_pkts_background_dl[i][j]);
				else
					otg_info->total_loss_ul+=(otg_info->nb_loss_pkts_ul[i][j][k] + otg_info->nb_loss_pkts_background_ul[i][j]);
			}
		}
	}
}


void kpi_gen() {
  int i, j,k;
  
  int tx_total_bytes_dl=0;
  int tx_total_pkts_dl=0;
  int rx_total_bytes_dl=0;
  int rx_total_pkts_dl=0;
  float min_owd_dl=0;
  float max_owd_dl=0;
  int tx_total_bytes_ul=0;
  int tx_total_pkts_ul=0;
  int rx_total_bytes_ul=0;
  int rx_total_pkts_ul=0;
  int tx_total_bytes_dl_background=0;
  int tx_total_pkts_dl_background=0;
  int rx_total_bytes_dl_background=0;
  int rx_total_pkts_dl_background=0;
  int tx_total_bytes_ul_background=0;
  int tx_total_pkts_ul_background=0;
  int rx_total_bytes_ul_background=0;
  int rx_total_pkts_ul_background=0;
  float min_owd_ul=0;
  float max_owd_ul=0;  

char traffic_type[12];
char traffic[30];

#ifdef STANDALONE	
  FILE *file;
  file = fopen("log_OTG.txt", "w"); 
#else   // Maybe to do modifo log function in order to clear file before a new write !!!! 
FILE *fc;
fc=fopen("/tmp/otg.log","w");;
  if(fc!=0) 
    fclose(fc);
#endif



  for (i=0; i<(NB_eNB_INST + NB_UE_INST); i++){
    for (j=0; j<(NB_eNB_INST + NB_UE_INST); j++){

/*background stats*/
if (i<NB_eNB_INST){
		tx_total_bytes_dl_background+=otg_info->tx_num_bytes_background[i][j];
	  tx_total_pkts_dl_background+=otg_info->tx_num_pkt_background[i][j];	
	  rx_total_bytes_dl_background+=otg_info->rx_num_bytes_background[i][j];
	  rx_total_pkts_dl_background+=otg_info->rx_num_pkt_background[i][j];

	}
	else{
		tx_total_bytes_ul_background+=otg_info->tx_num_bytes_background[i][j];
	  tx_total_pkts_ul_background+=otg_info->tx_num_pkt_background[i][j];	
	  rx_total_bytes_ul_background+=otg_info->rx_num_bytes_background[i][j];
	  rx_total_pkts_ul_background+=otg_info->rx_num_pkt_background[i][j];
}
     for (k=0; k<MAX_EMU_TRAFFIC; k++) {    
      tx_throughput(i,j,k);
      rx_goodput(i,j,k);
      rx_loss_rate_pkts(i,j,k);
      
      //LOG_I(OTG,"KPI: (src=%d, dst=%d) NB packet TX= %d,  NB packet RX= %d\n ",i, j,  otg_info->tx_num_pkt[i][j],  otg_info->rx_num_pkt[i][j]);
      
      
     if ((otg_info->tx_throughput[i][j][k]>0)||((otg_info->tx_throughput_background[i][j]>0) && (otg_info->tx_num_bytes[i][j][k]>0)))  {
 	if (i<NB_eNB_INST){
   	tx_total_bytes_dl+=otg_info->tx_num_bytes[i][j][k];
	  tx_total_pkts_dl+=otg_info->tx_num_pkt[i][j][k];	
	  rx_total_bytes_dl+=otg_info->rx_num_bytes[i][j][k];
	  rx_total_pkts_dl+=otg_info->rx_num_pkt[i][j][k];
   	/*tx_total_bytes_dl_background+=otg_info->tx_num_bytes_background[i][j];
	  tx_total_pkts_dl_background+=otg_info->tx_num_pkt_background[i][j];	
	  rx_total_bytes_dl_background+=otg_info->rx_num_bytes_background[i][j];
	  rx_total_pkts_dl_background+=otg_info->rx_num_pkt_background[i][j]; */
	  if ((min_owd_dl>otg_info->rx_owd_min[i][j][k]) || (min_owd_dl==0))
	    min_owd_dl=otg_info->rx_owd_min[i][j][k];
	  if ((max_owd_dl<otg_info->rx_owd_max[i][j][k]) || (max_owd_dl==0))
	    max_owd_dl=otg_info->rx_owd_max[i][j][k];
	}
	else{
   	tx_total_bytes_ul+=otg_info->tx_num_bytes[i][j][k];
	  tx_total_pkts_ul+=otg_info->tx_num_pkt[i][j][k];	
	  rx_total_bytes_ul+=otg_info->rx_num_bytes[i][j][k];
	  rx_total_pkts_ul+=otg_info->rx_num_pkt[i][j][k];
   	/*tx_total_bytes_ul_background+=otg_info->tx_num_bytes_background[i][j];
	  tx_total_pkts_ul_background+=otg_info->tx_num_pkt_background[i][j];	
	  rx_total_bytes_ul_background+=otg_info->rx_num_bytes_background[i][j];
	  rx_total_pkts_ul_background+=otg_info->rx_num_pkt_background[i][j];*/
	  if ((min_owd_ul>otg_info->rx_owd_min[i][j][k]) || (min_owd_ul==0))
	    min_owd_ul=otg_info->rx_owd_min[i][j][k];
	  if ((max_owd_ul<otg_info->rx_owd_max[i][j][k]) || (max_owd_ul==0))
	    max_owd_ul=otg_info->rx_owd_max[i][j][k];
	}

	//LOG_D(OTG,"KPI: (src=%d, dst=%d, appli %d) NB packet TX= %d,  NB packet RX= %d\n ",i, j,  otg_info->tx_num_pkt[i][j][k],  otg_info->rx_num_pkt[i][j][k]);

	if (g_otg->application_idx[i][j]>1)
		strcpy(traffic_type,"GATEWAY");
	else
		strcpy(traffic_type,"APPLICATION");


  switch  (k) {
    case  0 : 
			strcpy(traffic,"CUSTOMIZED TRAFFIC ");
       break;
     case 1 :
			strcpy(traffic,"M2M");
       break;
     case 2 :
			strcpy(traffic,"SCBR");
       break;
     case 3 :
			strcpy(traffic,"MCBR");
       break;
     case 4 :
			strcpy(traffic,"BCBR");
       break;
     case 5 :
			strcpy(traffic,"AUTO_PILOT");
       break;
     case 6 :
			strcpy(traffic,"BICYCLE_RACE");
       break;
     case 7 :
			strcpy(traffic,"OPENARENA");
       break;
     case 8 :
			strcpy(traffic,"TEAM_FORTRESS");
       break;
     case 9 :
			strcpy(traffic,"FULL_BUFFER");
       break;
     case 10 :
			strcpy(traffic,"M2M_TRAFFIC");
       break;
     case 11 :
			strcpy(traffic,"AUTO_PILOT_L");
       break;
     case 12 :
			strcpy(traffic,"AUTO_PILOT_M");
       break;
     case 13 :
			strcpy(traffic,"AUTO_PILOT_H");
       break;
     case 14 :
			strcpy(traffic,"AUTO_PILOT_E");
       break;
     case 15 :
			strcpy(traffic,"VIRTUAL_GAME_L");
       break;
     case 16 :
			strcpy(traffic,"VIRTUAL_GAME_M");
       break;
     case 17 :
			strcpy(traffic,"VIRTUAL_GAME_H");
       break;
     case 18 :
			strcpy(traffic,"VIRTUAL_GAME_F"); 
       break;
     case 19 :
			strcpy(traffic,"ALARM_HUMIDITY"); 
       break;
     case 20 :
			strcpy(traffic,"ALARM_SMOKE"); 
       break;
     case 21 :
			strcpy(traffic,"ALARM_TEMPERATURE"); 
       break;
     case 22 :
			strcpy(traffic,"OPENARENA_DL"); 
       break;
     case 23 :
			strcpy(traffic,"OPENARENA_UL"); 
       break;
     case 24 :
			strcpy(traffic,"VOIP_G711"); 
       break;
     case 25 :
			strcpy(traffic,"VOIP_G729"); 
       break;
     case 26 :
			strcpy(traffic,"IQSIM_MANGO"); 
       break;
     case 27 :
			strcpy(traffic,"IQSIM_NEWSTEO"); 
       break;
     case 28 :
			strcpy(traffic,"OPEMARENA_DL_TARMA"); 
       break;
     case 29 :
			strcpy(traffic,"VIDEO_VBR_10MBPS"); 
       break;
     case 30 :
			strcpy(traffic,"VIDEO_VBR_4MBPS"); 
       break;
     case 31 :
			strcpy(traffic,"VIDEO_VBR_2MBPS"); 
       break;
     case 32 :
			strcpy(traffic,"VIDEO_VBR_768KBPS"); 
       break;
     case 33 :
			strcpy(traffic,"VIDEO_VBR_384KBPS"); 
       break;
     case 34 :
			strcpy(traffic,"VIDEO_VBR_192KBPS"); 
       break;
 default:
       strcpy(traffic,"UKNOWN TRAFFIC"); 
 			break;
     }





#ifdef STANDALONE
	
	fprintf(file,"----------------------------------------------------------\n");	
  fprintf(file,"Total Time (ms)= %d \n", otg_info->ctime+1);
  if (i<NB_eNB_INST){
		fprintf(file,"[%s] DL [eNB:%d, UE:%d][%s] \n", traffic_type,i,j,traffic);}
	else
		fprintf(file,"[%s] UL [eNB:%d, UE:%d][%s] \n",traffic_type,j,i,traffic);
		fprintf(file,"[%s] Total packets(TX)= %d \n",traffic_type, otg_info->tx_num_pkt[i][j][k]);
		fprintf(file,"[%s] Total bytes(TX)= %d \n",traffic_type, otg_info->tx_num_bytes[i][j][k]);
		fprintf(file,"[%s] OWD MIN (one way)ms= %.2f \n",traffic_type, otg_info->rx_owd_min[i][j][k]);
		fprintf(file,"[%s] OWD MAX (one way)ms= %.2f \n",traffic_type, otg_info->rx_owd_max[i][j][k]);
		fprintf(file,"[%s] TX throughput = %.7f(Kbit/s) \n",traffic_type, otg_info->tx_throughput[i][j][k]);
		fprintf(file,"[%s] RX goodput= %.7f (K/s) \n",traffic_type, otg_info->rx_goodput[i][j][k]);
		if (otg_info->rx_loss_rate[i][j[k]]>0){
	  	fprintf(file,"[%s] Loss rate(percentage)= %.2f \n",traffic_type, (otg_info->rx_loss_rate[i][j][k]*100));
	  	fprintf(file,"[%s] NB Lost  packets=%d \n",traffic_type, (otg_info->tx_num_pkt[i][j][k]-otg_info->rx_num_pkt[i][j][k]));
	  	//fprintf(file,"[%s] NB Lost [OTG] packets=%d \n",traffic_type, otg_info->nb_loss_pkts_otg[i][j]);
		}

 /* if ((g_otg->background_stats==1)&&(otg_info->tx_num_bytes_background[i][j]>0)){
    fprintf(file,"[BACKGROUND] Total packets(TX)= %d \n", otg_info->tx_num_pkt_background[i][j]);
	  fprintf(file,"[BACKGROUND] Total bytes(TX)= %d \n", otg_info->tx_num_bytes_background[i][j]);
	  fprintf(file,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", otg_info->tx_throughput_background[i][j]);
	  fprintf(file,"[BACKGROUND] RX goodput= %.7f (Kbit/s) \n", otg_info->rx_goodput_background[i][j]);
	  if (otg_info->rx_loss_rate_background[i][j]>0){
	    fprintf(file,"[BACKGROUND] Loss rate(percentage)= %lf \n", (otg_info->rx_loss_rate_background[i][j]*100));
	    fprintf(file,"[BACKGROUND] NB Lost  packets=%d \n", (otg_info->tx_num_pkt_background[i][j]-otg_info->rx_num_pkt_background[i][j]));
	  }
	}
*/


#else
  LOG_I(OTG,"----------------------------------------------------------\n");
  LOG_I(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
  if (i<NB_eNB_INST){
    LOG_I(OTG,"[%s] DL [eNB:%d -> UE:%d][%s] \n",traffic_type, i, j, traffic);}
  else
    LOG_I(OTG,"[%s] UL [UE:%d -> eNB:%d][%s] \n",traffic_type, i, j, traffic);
  LOG_I(OTG,"[%s] Total packets(TX)= %d \n",traffic_type, otg_info->tx_num_pkt[i][j][k]);
		LOG_I(OTG,"[%s] Total bytes(TX)= %d \n",traffic_type, otg_info->tx_num_bytes[i][j][k]);
		LOG_I(OTG,"[%s] OWD MIN (one way)ms= %.2f \n",traffic_type, otg_info->rx_owd_min[i][j][k]);
		LOG_I(OTG,"[%s] OWD MAX (one way)ms= %.2f \n",traffic_type, otg_info->rx_owd_max[i][j][k]);
		LOG_I(OTG,"[%s] TX throughput = %.7f(Kbit/s) \n",traffic_type, otg_info->tx_throughput[i][j][k]);
		LOG_I(OTG,"[%s] RX goodput= %.7f (Kbit/s) \n",traffic_type, otg_info->rx_goodput[i][j][k]);
	if (otg_info->rx_loss_rate[i][j][k]>0){
	  LOG_I(OTG,"[%s] Loss rate(percentage)= %.2f \n",traffic_type, (otg_info->rx_loss_rate[i][j][k]*100));
	  LOG_I(OTG,"[%s] NB Lost  packets= %d \n",traffic_type, (otg_info->tx_num_pkt[i][j]-otg_info->rx_num_pkt[i][j][k]));
	  //LOG_D(OTG,"[%s] NB Lost [OTG] packets=%d \n",traffic_type, otg_info->nb_loss_pkts_otg[i][j]);
	}
/*  if ((g_otg->background_stats==1)&&(otg_info->tx_num_bytes_background[i][j]>0)){
    LOG_I(OTG,"[BACKGROUND] Total packets(TX)= %d \n", otg_info->tx_num_pkt_background[i][j]);
	  LOG_I(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", otg_info->tx_num_bytes_background[i][j]);
	  LOG_I(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", otg_info->tx_throughput_background[i][j]);
	  LOG_I(OTG,"[BACKGROUND] RX goodput= %.7f (Kbit/s) \n", otg_info->rx_goodput_background[i][j]);
	  if (otg_info->rx_loss_rate_background[i][j]>0){
	    LOG_I(OTG,"[BACKGROUND] Loss rate(percentage)= %.2f \n", (otg_info->rx_loss_rate_background[i][j]*100));
	    LOG_I(OTG,"[BACKGROUND] NB Lost  packets=%d \n", (otg_info->tx_num_pkt_background[i][j]-otg_info->rx_num_pkt_background[i][j]));
	  }
	}
*/
	LOG_F(OTG,"----------------------------------------------------------\n");
	LOG_F(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
	if (i<NB_eNB_INST){
		LOG_F(OTG,"[%s] DL [eNB:%d -> UE:%d][%s] \n",traffic_type ,i, j, traffic);}
	else
		LOG_F(OTG,"[%s] UL [Ue:%d -> eNB:%d][%s] \n",traffic_type, i, j,traffic);
		LOG_F(OTG,"[%s] Total packets(TX)= %d \n",traffic_type, otg_info->tx_num_pkt[i][j][k]);
		LOG_F(OTG,"[%s] Total bytes(TX)= %d \n",traffic_type, otg_info->tx_num_bytes[i][j][k]);
		LOG_F(OTG,"[%s] OWD MIN (one way)ms= %.2f \n",traffic_type, otg_info->rx_owd_min[i][j][k]);
		LOG_F(OTG,"[%s] OWD MAX (one way)ms= %.2f \n",traffic_type, otg_info->rx_owd_max[i][j][k]);
		LOG_F(OTG,"[%s] TX throughput = %.7f(Kbit/s) \n",traffic_type, otg_info->tx_throughput[i][j][k]);
		LOG_F(OTG,"[%s] RX goodput= %.7f (Kbit/s) \n",traffic_type, otg_info->rx_goodput[i][j][k]);
	if (otg_info->rx_loss_rate[i][j][k]>0){
	  LOG_F(OTG,"[%s] Loss rate(percentage)= %.2f \n",traffic_type, (otg_info->rx_loss_rate[i][j][k]*100));
	  LOG_F(OTG,"[%s] NB Lost  packets= %d \n",traffic_type,(otg_info->tx_num_pkt[i][j][k]-otg_info->rx_num_pkt[i][j][k]));
    //LOG_D(OTG,"[%s] NB Lost [OTG] packets=%d \n",traffic_type, otg_info->nb_loss_pkts_otg[i][j]);
	}
/*  if ((g_otg->background_stats==1)&&(otg_info->tx_num_bytes_background[i][j]>0)){
  	LOG_F(OTG,"[BACKGROUND] Total packets(TX)= %d \n", otg_info->tx_num_pkt_background[i][j]);
	  LOG_F(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", otg_info->tx_num_bytes_background[i][j]);
	  LOG_F(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", otg_info->tx_throughput_background[i][j]);
	  LOG_F(OTG,"[BACKGROUND] RX goodput= %.7f (Kbit/s) \n", otg_info->rx_goodput_background[i][j]);
	  if (otg_info->rx_loss_rate_background[i][j]>0){
	    LOG_F(OTG,"[BACKGROUND] Loss rate(percentage)= %.2f \n", (otg_info->rx_loss_rate_background[i][j]*100));
	    LOG_F(OTG,"[BACKGROUND] NB Lost  packets=%d \n", (otg_info->tx_num_pkt_background[i][j]-otg_info->rx_num_pkt_background[i][j]));
	  }
	}
*/
#endif 

      }
    }


#ifdef STANDALONE

if ((g_otg->background_stats==1)&&(otg_info->tx_num_bytes_background[i][j]>0)){
	fprintf(file,"----------------------------------------------------------\n");	
 fprintf(file,"Total Time (ms)= %d \n", otg_info->ctime+1);
  if (i<NB_eNB_INST){
		fprintf(file,"[%s] DL [eNB:%d, UE:%d] \n", traffic_type,i,j);}
	else
		fprintf(file,"[%s] UL [eNB:%d, UE:%d] \n",traffic_type,j,i);

    fprintf(file,"[BACKGROUND] Total packets(TX)= %d \n", otg_info->tx_num_pkt_background[i][j]);
	  fprintf(file,"[BACKGROUND] Total bytes(TX)= %d \n", otg_info->tx_num_bytes_background[i][j]);
	  fprintf(file,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", otg_info->tx_throughput_background[i][j]);
	  fprintf(file,"[BACKGROUND] RX goodput= %.7f (Kbit/s) \n", otg_info->rx_goodput_background[i][j]);
	  if (otg_info->rx_loss_rate_background[i][j]>0){
	    fprintf(file,"[BACKGROUND] Loss rate(percentage)= %lf \n", (otg_info->rx_loss_rate_background[i][j]*100));
	    fprintf(file,"[BACKGROUND] NB Lost  packets=%d \n", (otg_info->tx_num_pkt_background[i][j]-otg_info->rx_num_pkt_background[i][j]));
	  }
	}
#else
if ((g_otg->background_stats==1)&&(otg_info->tx_num_bytes_background[i][j]>0)){
 LOG_I(OTG,"----------------------------------------------------------\n");
  LOG_I(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
  if (i<NB_eNB_INST){
    LOG_I(OTG,"[%s] DL [eNB:%d -> UE:%d] \n",traffic_type, i, j);}
  else
    LOG_I(OTG,"[%s] UL [UE:%d -> eNB:%d] \n",traffic_type, i, j);

    LOG_I(OTG,"[BACKGROUND] Total packets(TX)= %d \n", otg_info->tx_num_pkt_background[i][j]);
	  LOG_I(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", otg_info->tx_num_bytes_background[i][j]);
	  LOG_I(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", otg_info->tx_throughput_background[i][j]);
	  LOG_I(OTG,"[BACKGROUND] RX goodput= %.7f (Kbit/s) \n", otg_info->rx_goodput_background[i][j]);
	  if (otg_info->rx_loss_rate_background[i][j]>0){
	    LOG_I(OTG,"[BACKGROUND] Loss rate(percentage)= %.2f \n", (otg_info->rx_loss_rate_background[i][j]*100));
	    LOG_I(OTG,"[BACKGROUND] NB Lost  packets=%d \n", (otg_info->tx_num_pkt_background[i][j]-otg_info->rx_num_pkt_background[i][j]));
	  }
	}

if ((g_otg->background_stats==1)&&(otg_info->tx_num_bytes_background[i][j]>0)){
	LOG_F(OTG,"----------------------------------------------------------\n");
	LOG_F(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
	if (i<NB_eNB_INST){
		LOG_F(OTG,"[%s] DL [eNB:%d -> UE:%d] \n",traffic_type ,i, j);}
	else
		LOG_F(OTG,"[%s] UL [Ue:%d -> eNB:%d] \n",traffic_type, i, j);

  	LOG_F(OTG,"[BACKGROUND] Total packets(TX)= %d \n", otg_info->tx_num_pkt_background[i][j]);
	  LOG_F(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", otg_info->tx_num_bytes_background[i][j]);
	  LOG_F(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", otg_info->tx_throughput_background[i][j]);
	  LOG_F(OTG,"[BACKGROUND] RX goodput= %.7f (Kbit/s) \n", otg_info->rx_goodput_background[i][j]);
	  if (otg_info->rx_loss_rate_background[i][j]>0){
	    LOG_F(OTG,"[BACKGROUND] Loss rate(percentage)= %.2f \n", (otg_info->rx_loss_rate_background[i][j]*100));
	    LOG_F(OTG,"[BACKGROUND] NB Lost  packets=%d \n", (otg_info->tx_num_pkt_background[i][j]-otg_info->rx_num_pkt_background[i][j]));
	  }
	}
#endif


		}	
  }
#ifdef STANDALONE
  fprintf (file,"**************** TOTAL DL RESULTS ******************\n");
  fprintf(file,"Total Time= %d \n", otg_info->ctime+1);
  fprintf(file,"[DATA] Total packets(TX)= %d \n", tx_total_pkts_dl);
  fprintf(file,"[DATA] Total bytes(TX)= %d \n", tx_total_bytes_dl);
  fprintf(file,"[DATA] Total packets(RX)= %d \n", rx_total_pkts_dl);
  fprintf(file,"[DATA] Total bytes(RX)= %d \n", rx_total_bytes_dl);
  fprintf(file,"[DATA] OWD MIN (one way)ms= %.2f \n", min_owd_dl);
  fprintf(file,"[DATA] OWD MAX (one way)ms= %.2f \n", max_owd_dl);
  fprintf(file,"[DATA] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_dl*1000*8)/(otg_info->ctime*1024));
  fprintf(file,"[DATA] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_dl*1000*8)/(otg_info->ctime*1024));
  if ((g_otg->background_stats==1)&&(tx_total_pkts_dl_background>0)){
    fprintf(file,"[BACKGROUND] Total packets(TX)= %d \n", tx_total_pkts_dl_background);
    fprintf(file,"[BACKGROUND] Total bytes(TX)= %d \n", tx_total_bytes_dl_background);
    fprintf(file,"[BACKGROUND] Total packets(RX)= %d \n", rx_total_pkts_dl_background);
    fprintf(file,"[BACKGROUND] Total bytes(RX)= %d \n", rx_total_bytes_dl_background);
    fprintf(file,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_dl_background*1000*8)/(otg_info->ctime*1024));
    fprintf(file,"[BACKGROUND] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_dl_background*1000*8)/(otg_info->ctime*1024));
  }
  fprintf (file,"**************** TOTAL UL RESULTS ******************\n");
  fprintf(file,"Total Time (ms)= %d \n", otg_info->ctime+1);
  fprintf(file,"[DATA] Total packets(TX)= %d \n", tx_total_pkts_ul);
  fprintf(file,"[DATA] Total bytes(TX)= %d \n", tx_total_bytes_ul);
  fprintf(file,"[DATA] Total packets(RX)= %d \n", rx_total_pkts_ul);
  fprintf(file,"[DATA] Total bytes(RX)= %d \n", rx_total_bytes_ul);
  fprintf(file,"[DATA] OWD MIN (one way)ms= %.2f \n", min_owd_ul);
  fprintf(file,"[DATA] OWD MAX (one way)ms= %.2f \n", max_owd_ul);
  fprintf(file,"[DATA] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_ul*1000*8)/(otg_info->ctime*1024));
  fprintf(file,"[DATA] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_ul*1000*8)/(otg_info->ctime*1024));
  if ((g_otg->background_stats==1)&&(tx_total_pkts_ul_background>0)){
    fprintf(file,"[BACKGROUND] Total packets(TX)= %d \n", tx_total_pkts_ul_background);
    fprintf(file,"[BACKGROUND] Total bytes(TX)= %d \n", tx_total_bytes_ul_background);
    fprintf(file,"[BACKGROUND] Total packets(RX)= %d \n", rx_total_pkts_ul_background);
    fprintf(file,"[BACKGROUND] Total bytes(RX)= %d \n", rx_total_bytes_ul_background);
    fprintf(file,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_ul_background*1000*8)/(otg_info->ctime*1024));
    fprintf(file,"[BACKGROUND] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_ul_background*1000*8)/(otg_info->ctime*1024));
  }
  fclose(file);
#else
  LOG_I(OTG,"**************** TOTAL DL RESULTS ******************\n");
  LOG_I(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
  LOG_I(OTG,"[DATA] Total packets(TX)= %d \n", tx_total_pkts_dl);
  LOG_I(OTG,"[DATA] Total packets(RX)= %d \n", rx_total_pkts_dl);
  LOG_I(OTG,"[DATA] Total bytes(TX)= %d \n", tx_total_bytes_dl);
  LOG_I(OTG,"[DATA] Total bytes(RX)= %d \n", rx_total_bytes_dl);
  LOG_I(OTG,"[DATA] OWD MIN (one way)ms= %.2f \n", min_owd_dl);
  LOG_I(OTG,"[DATA] OWD MAX (one way)ms= %.2f \n", max_owd_dl);
  LOG_I(OTG,"[DATA] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_dl*1000*8)/(otg_info->ctime*1024));
  LOG_I(OTG,"[DATA] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_dl*1000*8)/(otg_info->ctime*1024));
  if ((g_otg->background_stats==1)&&(tx_total_pkts_dl_background>0)){
    LOG_I(OTG,"[BACKGROUND] Total packets(TX)= %d \n", tx_total_pkts_dl_background);
    LOG_I(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", tx_total_bytes_dl_background);
    LOG_I(OTG,"[BACKGROUND] Total packets(RX)= %d \n", rx_total_pkts_dl_background);
    LOG_I(OTG,"[BACKGROUND] Total bytes(RX)= %d \n", rx_total_bytes_dl_background);
    LOG_I(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_dl_background*1000*8)/(otg_info->ctime*1024));
    LOG_I(OTG,"[BACKGROUND] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_dl_background*1000*8)/(otg_info->ctime*1024));
	}

  LOG_F(OTG,"**************** TOTAL DL RESULTS ******************\n");
  LOG_F(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
  LOG_F(OTG,"[DATA] Total packets(TX)= %d \n", tx_total_pkts_dl);
  LOG_F(OTG,"[DATA] Total packets(RX)= %d \n", rx_total_pkts_dl);
  LOG_F(OTG,"[DATA] Total bytes(TX)= %d \n", tx_total_bytes_dl);
  LOG_F(OTG,"[DATA] Total bytes(RX)= %d \n", rx_total_bytes_dl);
  LOG_F(OTG,"[DATA] OWD MIN (one way)ms= %.2f \n", min_owd_dl);
  LOG_F(OTG,"[DATA] OWD MAX (one way)ms= %.2f \n", max_owd_dl);
  LOG_F(OTG,"[DATA] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_dl*1000*8)/(otg_info->ctime*1024));
  LOG_F(OTG,"[DATA] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_dl*1000*8)/(otg_info->ctime*1024));
  if ((g_otg->background_stats==1)&&(tx_total_pkts_dl_background>0)){
    LOG_F(OTG,"[BACKGROUND] Total packets(TX)= %d \n", tx_total_pkts_dl_background);
    LOG_F(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", tx_total_bytes_dl_background);
    LOG_F(OTG,"[BACKGROUND] Total packets(RX)= %d \n", rx_total_pkts_dl_background);
    LOG_F(OTG,"[BACKGROUND] Total bytes(RX)= %d \n", rx_total_bytes_dl_background);
    LOG_F(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_dl_background*1000*8)/(otg_info->ctime*1024));
    LOG_F(OTG,"[BACKGROUND] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_dl_background*1000*8)/(otg_info->ctime*1024));
	}

  
	LOG_I(OTG,"**************** TOTAL UL RESULTS ******************\n");
  LOG_I(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
  LOG_I(OTG,"[DATA] Total packets(TX)= %d \n", tx_total_pkts_ul);
  LOG_I(OTG,"[DATA] Total packets(RX)= %d \n", rx_total_pkts_ul);
  LOG_I(OTG,"[DATA] Total bytes(TX)= %d \n", tx_total_bytes_ul);
  LOG_I(OTG,"[DATA] Total bytes(RX)= %d \n", rx_total_bytes_ul);
  LOG_I(OTG,"[DATA] OWD MIN (one way)ms= %.2f \n", min_owd_ul);
  LOG_I(OTG,"[DATA] OWD MAX (one way)ms= %.2f \n", max_owd_ul);
  LOG_I(OTG,"[DATA] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_ul*1000*8)/(otg_info->ctime*1024));
  LOG_I(OTG,"[DATA] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_ul*1000*8)/(otg_info->ctime*1024));
  if ((g_otg->background_stats==1)&&(tx_total_pkts_ul_background>0)){
    LOG_I(OTG,"[BACKGROUND] Total packets(TX)= %d \n", tx_total_pkts_ul_background);
    LOG_I(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", tx_total_bytes_ul_background);
    LOG_I(OTG,"[BACKGROUND] Total packets(RX)= %d \n", rx_total_pkts_ul_background);
    LOG_I(OTG,"[BACKGROUND] Total bytes(RX)= %d \n", rx_total_bytes_ul_background);
    LOG_I(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_ul_background*1000*8)/(otg_info->ctime*1024));
    LOG_I(OTG,"[BACKGROUND] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_ul_background*1000*8)/(otg_info->ctime*1024));

  }
	LOG_F(OTG,"**************** TOTAL UL RESULTS ******************\n");
  LOG_F(OTG,"Total Time (ms)= %d \n", otg_info->ctime+1);
  LOG_F(OTG,"[DATA] Total packets(TX)= %d \n", tx_total_pkts_ul);
  LOG_F(OTG,"[DATA] Total packets(RX)= %d \n", rx_total_pkts_ul);
  LOG_F(OTG,"[DATA] Total bytes(TX)= %d \n", tx_total_bytes_ul);
  LOG_F(OTG,"[DATA] Total bytes(RX)= %d \n", rx_total_bytes_ul);
  LOG_F(OTG,"[DATA] OWD MIN (one way)ms= %.2f \n", min_owd_ul);
  LOG_F(OTG,"[DATA] OWD MAX (one way)ms= %.2f \n", max_owd_ul);
  LOG_F(OTG,"[DATA] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_ul*1000*8)/(otg_info->ctime*1024));
  LOG_F(OTG,"[DATA] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_ul*1000*8)/(otg_info->ctime*1024));
  if ((g_otg->background_stats==1)&&(tx_total_pkts_ul_background>0)){
    LOG_F(OTG,"[BACKGROUND] Total packets(TX)= %d \n", tx_total_pkts_ul_background);
    LOG_F(OTG,"[BACKGROUND] Total bytes(TX)= %d \n", tx_total_bytes_ul_background);
    LOG_F(OTG,"[BACKGROUND] Total packets(RX)= %d \n", rx_total_pkts_ul_background);
    LOG_F(OTG,"[BACKGROUND] Total bytes(RX)= %d \n", rx_total_bytes_ul_background);
    LOG_F(OTG,"[BACKGROUND] TX throughput = %.7f(Kbit/s) \n", ((double)tx_total_bytes_ul_background*1000*8)/(otg_info->ctime*1024));
    LOG_F(OTG,"[BACKGROUND] RX throughput = %.7f(Kbit/s) \n", ((double)rx_total_bytes_ul_background*1000*8)/(otg_info->ctime*1024));

  }

#endif
}


void add_log_metric(int src, int dst, int ctime, double metric, unsigned int label){
 unsigned int i;
 unsigned int j;
 unsigned int node_actif=0;

 //LOG_I(OTG,"[%d][%d] LOGG_ADDED ctime=%d, metric=%.2f  \n", src, dst, ctime, metric);

 switch (label) {
 case OTG_LATENCY:
   add_log_label(label, &start_log_latency);
   break;
 case OTG_LATENCY_BG:
   add_log_label(label, &start_log_latency_bg);
   break;
 case OTG_GP:
	 add_log_label(label, &start_log_GP);
	 break;
 case OTG_GP_BG:
	 add_log_label(label, &start_log_GP_bg);
	 break;
 default:
   LOG_E(OTG, "File label unknown \n");
 }

 LOG_F(label,"%d  ", ctime);
  for (i=0; i<=(NB_eNB_INST + NB_UE_INST); i++){
    for (j=0; j<=(NB_eNB_INST + NB_UE_INST); j++){
    node_actif=0;
        if ((g_otg->idt_dist[i][j][0][PE_STATE]>0) || (g_otg->application_type[i][j][0] >0))
					node_actif=1;

      if ((node_actif>0) && ((i==src) && (j==dst)))
          LOG_F(label,"  %f  ", metric);
      if  ((node_actif>0) && ((i!=src) || (j!=dst)))
          LOG_F(label,"  %d  ", 0);
  }
 }
 LOG_F(label,"%f\n", metric);
}



void  add_log_label(unsigned int label, unsigned int * start_log_metric){
 unsigned int i;
 unsigned int j;
 unsigned int node_actif=0;

 if (*start_log_metric==0){
 *start_log_metric=1;
   LOG_F(label,"Time   ");
   for (i=0; i<=(NB_eNB_INST + NB_UE_INST); i++){
     for (j=0; j<=(NB_eNB_INST + NB_UE_INST); j++){
       node_actif=0;
          if (g_otg->idt_dist[i][j][0][PE_STATE]>0 )
	    node_actif++; 
      if (node_actif>0)
        LOG_F(label,"%d->%d    ", i, j);  
    }
   }
   LOG_F(label,"Aggregated\n");
 }
}

