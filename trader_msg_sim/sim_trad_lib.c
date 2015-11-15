#include "sim_trad_lib.h"


static char *st_name = "STRA_MY_CAPITAL";
static char *broker_id = "2000";
static char *account = "20151112";
static struct node *contr_ar;
static char *g_all_contr;
static double order_price = 0.0; 
static unsigned int  s_buy_qty = 0;


sim_trader_t *
sim_trader_init(trad_sim_cfg_t *cfg)
{
	sim_trader_t *sim_data;
	sim_data = calloc(1,sizeof(sim_trader_t));	
	if (NULL == sim_data) {
		syslog(LOG_ERR, "calloc sim_data was failed :\n");
		return NULL;
	}

	sim_data->interval = cfg->interval;
	sim_data->exchg_type = cfg->exchg_type;
	sim_data->tot_size = (cfg->tot_time*1000)/cfg->interval;
	
	return sim_data;
}

unsigned int 
sim_trader_size(sim_trader_t  *sim_data)
{
	if (NULL == sim_data) {
		syslog(LOG_ERR,"IN sim_trader_size() deteched sim_data was NULL \n");
		return -1;
	}
	return sim_data->tot_size;
}

int 
extract_contract(const char * file_path , int *count)
{
	int idx = 0 , contr_idx = 0 , contr_size_idx = 0, tmp_len = 0 , tot_len = 0;	
	char *tmp , t;

	FILE *fd = fopen(file_path,"r");
	char buf[BUF_SIZE];
	while(fgets(buf,BUF_SIZE,fd)) {
		contr_size_idx++;
	}
	fclose(fd);
	
	
	int contr_size =  contr_size_idx;
	tot_len = contr_size * sizeof(struct  node);
	*count =  contr_size_idx;
	contr_ar = (struct node *)malloc(tot_len);
	if (contr_ar == NULL) {
		printf("contr_ar malloc IS failed \n");
		return -1;
	}

	tmp = &t ;
	/* g_all_contr is global var  */
	g_all_contr =  calloc(1, tot_len);
	if (g_all_contr == NULL) {
		printf("contr_ar malloc IS failed \n");
		return -1;
	}
	
	fd = fopen(file_path,"r");
	while(fgets(buf,BUF_SIZE,fd)) {
		tmp = strstr(buf,";");
		int len = tmp - buf;
		buf[len] = '\0';
		strncpy(contr_ar[idx].contract, buf, len+1);
		
		tmp_len += snprintf(g_all_contr + tmp_len, tot_len - tmp_len, "%s,", buf);
		idx++;
	}
	g_all_contr[tmp_len] = '\0';
	
	fclose(fd);	
	
#if  0 /*for test*/	
	for (contr_idx = 0; contr_idx < contr_size; contr_idx++) {
		printf("%s\n", contr_ar[contr_idx].contract );
	}
#endif

	return 0;
}


int 
send_stra_rsp(response_t *rsp , int fd)
{
	char *user = "MY_008";
	strategy_resp_t *stra_rsp;
	stra_rsp = (strategy_resp_t *)rsp->data;

	/* constructor  message head */
	rsp->id = 0;
	rsp->type = M_RESP_S;
	rsp->len = STRA_RSP_LEN - RSP_LEN;

	/* constructor message body */
	int len = 0;
	len = strlen(st_name);
	memcpy(stra_rsp->name, st_name, len);
	stra_rsp->name[len] = '\0';

	len = strlen(account);
	memcpy(stra_rsp->account, account, len);
	stra_rsp->account[len] = '\0';
	
	len = strlen(user);
	memcpy(stra_rsp->user, user, strlen(user));
	stra_rsp->user[len] = '\0';

	len = strlen(broker_id);
	memcpy(stra_rsp->broker_id, broker_id, strlen(broker_id));
	stra_rsp->broker_id[len] = '\0';

	/* status default 0 */

	/* set message tail */
	stra_rsp->param[0] |= SET_TAIL; 

	while (1) {
		int ret = send(fd, rsp , STRA_RSP_LEN, 0);
		if ((-1 == ret) && (errno == EWOULDBLOCK || errno == EAGAIN)) {
				continue;
		} 
		else if(-1 == ret) {
			syslog(LOG_ERR, "send() strategy_rsp  is failed ! : %s\n" , strerror(errno));
			goto err_exit;
		}
		break;
	}
	return 0;

err_exit:
	if (fd > 0) {
		close(fd);
		syslog(LOG_ERR, "send() strategy_rsp  fd  is close ! \n");
	}
	return -1;
}

int 
send_contr_rsp(response_t *rsp, int fd)
{
	char *symbols = "MY1512"; 
	contract_resp_t *contr_rsp;
	contr_rsp = (contract_resp_t *)rsp->data;

	/* constructor  message head */
	rsp->id = 0;
	rsp->type = M_RESP_C;
	rsp->len = CONTR_RSP_LEN - RSP_LEN;

	/* constructor message body */
	int len = 0;
	len = strlen(st_name);
	memcpy(contr_rsp->st_name, st_name, len);
	contr_rsp->st_name[len] = '\0';

	len = strlen(symbols);
	memcpy(contr_rsp->symbols, symbols, len);
	contr_rsp->symbols[len] = '\0';

	/* set message tail */
	rsp->data[rsp->len] |= SET_TAIL; 

	while (1) {
		int ret = send(fd, rsp , STRA_RSP_LEN, 0);
		if ((-1 == ret) && (errno == EWOULDBLOCK || errno == EAGAIN)) {
				continue;
		} 
		else if(-1 == ret) {
			syslog(LOG_ERR, "send() contr_rsp  is failed ! : %s\n" , strerror(errno));
			goto err_exit;
		}
		break;
	}
	return 0;

err_exit:
	if (fd > 0) {
		close(fd);
		syslog(LOG_ERR, "send() contr_rsp  fd  is close ! \n");
	}
	return -1;
}

int 
send_order_rsp(response_t *rsp, int fd ,int idx)
{
	order_resp_t *order_rsp;
	order_rsp = (order_resp_t *)rsp->data;

	/* constructor  message head */
	rsp->id = 0;
	rsp->type = M_RESP_O;
	rsp->len = ORD_RSP_LEN - RSP_LEN;

	/* constructor message body */

	/* time : struct timeval inital 0 */
	int len = 0;
	len = strlen(st_name);
	memcpy(order_rsp->st_name, st_name, len) ;
	order_rsp->st_name[len] = '\0';

	strncpy(order_rsp->contract,  contr_ar[idx].contract, sizeof(contr_ar[idx].contract));
	/* order_id set 0 */

	len = strlen(broker_id);
	memcpy(order_rsp->broker_id, broker_id, strlen(broker_id));
	order_rsp->broker_id[len] = '\0';

	/* status init 0 */
	/* buy --> 0 , sell-->1 , default 0 */
	order_rsp->vol = 1;
	
	order_rsp->price = order_price;
	order_price = order_price + 1.0;
	
	/* instr default 0 */
	
	/* type default 0 */

	order_rsp->filled_price = order_rsp->price;

	/* rejected_reason default 0 */
	/* note default 0 */
	/* set message tail */
	rsp->data[rsp->len] |= SET_TAIL; 

	while (1) {
		int ret = send(fd, rsp , ORD_RSP_LEN, 0);
		if ((-1 == ret) && (errno == EWOULDBLOCK || errno == EAGAIN)) {
				continue;
		} 
		else if(-1 == ret) {
			syslog(LOG_ERR, "send() order_rsp  is failed ! : %s\n" , strerror(errno));
			goto err_exit;
		}
		break;
	}
	return 0;

err_exit:
	if (fd > 0) {
		close(fd);
		syslog(LOG_ERR, "send() order_rsp  fd  is close ! \n");
	}
	return -1;	
}

int 
send_pos_rsp(response_t *rsp, int fd, int idx)
{
	position_resp_t *pos_rsp;
	pos_rsp = (position_resp_t *)rsp->data;

	/* constructor  message head */
	rsp->id = 0;
	rsp->type = M_RESP_P;
	rsp->len = POS_RSP_LEN - RSP_LEN;

	/* constructor message body */
	int len = strlen(account);
	memcpy(pos_rsp->account, account, len);
	pos_rsp->account[len] = '\0';
	
	len = strlen(st_name);
	memcpy(pos_rsp->st_name, st_name, len);
	pos_rsp->st_name[len] = '\0';
	
	strncpy(pos_rsp->contract,  contr_ar[idx].contract, sizeof(contr_ar[idx].contract));

	pos_rsp->buy_qty = s_buy_qty;
	s_buy_qty = s_buy_qty + 1; 
	
	/* sell_qty default 0*/

	/* avg_buy_price default 0 */

	/* avg_sell_price default 0 */
	/* set message tail */
	rsp->data[rsp->len] |= SET_TAIL; 

	while (1) {
		int ret = send(fd, rsp , POS_RSP_LEN, 0);
		if ((-1 == ret) && (errno == EWOULDBLOCK || errno == EAGAIN)) {
				continue;
		} 
		else if(-1 == ret) {
			syslog(LOG_ERR, "send() pos_rsp  is failed ! : %s\n" , strerror(errno));
			goto err_exit;
		}
		break;
	}
	return 0;

err_exit:
	if (fd > 0) {
		close(fd);
		syslog(LOG_ERR, "send() pos_rsp  fd  is close ! \n");
	}
	return -1;	
}

int 
sim_trader_start(sim_trader_t  *sim_data, int fd)
{
	if (NULL == sim_data) {
		syslog(LOG_ERR,"IN sim_trader_start() deteched sim_data was NULL \n");
		return -1;
	}
	printf("Come to sim_trader_start() \n");
	int idx = 0, contr_idx = 0, contr_size_idx = 0, contr_size = 0, tot_size = 0, exchg_type = 0;	
	int ret = 0;
	exchg_type = sim_data->exchg_type;

	switch(exchg_type) {
		case 0:
			ret = extract_contract("CFEX_CONTR.TXT", &contr_size);
			if (-1 == ret ) {
				syslog(LOG_ERR,"extract_contract() CFEX_CONTR.TXT IS failed \n");
				return -1;
			}
			break;
		case 1 ... 5:
			ret = extract_contract("DCE_CONTR.TXT", &contr_size);
			if (-1 == ret ) {
				syslog(LOG_ERR,"extract_contract() DCE_CONTR.TXT IS failed \n");
				return -1;
			}
			break;
		case 6:
			ret = extract_contract("SHFE_CONTR.TXT", &contr_size);
			if (-1 == ret ) {
				syslog(LOG_ERR,"extract_contract() SHFE_CONTR.TXT IS failed \n");
				return -1;
			}
			break;
		case 7 ... 8:
			ret = extract_contract("CZCE_CONTR.TXT", &contr_size);
			if (-1 == ret ) {
				syslog(LOG_ERR,"extract_contract() CZCE_CONTR.TXT IS failed \n");
				return -1;
			}
			break;
		case 9 ... 10:
			ret = extract_contract("STOCK_CONTR.TXT", &contr_size);
			if (-1 == ret ) {
				syslog(LOG_ERR,"extract_contract() STOCK_CONTR.TXT IS failed \n");
				return -1;
			}
			break;
		default :
			syslog(LOG_ERR, "req->type is error \n");
	}
	
	response_t  *strategy_rsp, *order_rsp,  *pos_rsp, *contr_rsp;

	strategy_rsp = (response_t *)calloc(1, STRA_RSP_LEN); 
	order_rsp = (response_t *)calloc(1, ORD_RSP_LEN); 
	pos_rsp = (response_t *)calloc(1, POS_RSP_LEN);
	contr_rsp = (response_t *)calloc(1, CONTR_RSP_LEN); 

	ret = send_stra_rsp(strategy_rsp, fd);
	if (-1 == ret) {
		syslog(LOG_ERR, "send() send_stra_rsp() is failed !\n");
		goto err_exit;
	} 

	ret = send_contr_rsp(contr_rsp, fd);
	if (-1 == ret) {
		syslog(LOG_ERR, "send() send_contr_rsp() is failed !\n");
		goto err_exit;
	} 
 	

	tot_size = sim_data->tot_size;
	for (idx = 0; idx < tot_size; idx++) {
		for (contr_idx = 0; contr_idx < contr_size; contr_idx++) {
			
			ret = send_order_rsp(order_rsp, fd, idx);
			if (-1 == ret) {
				syslog(LOG_ERR, "send() send_order_rsp() is failed !\n");
				goto err_exit;
			} 

			ret = send_pos_rsp(pos_rsp, fd, idx);
			if (-1 == ret) {
				syslog(LOG_ERR, " send() send_pos_rsp() is failed !\n");
				goto err_exit;
			} 

		}
		usleep(sim_data->interval);
	}

	free(strategy_rsp);
	free(order_rsp);
	free(pos_rsp);
	free(contr_rsp);

	return 0;
err_exit:
		free(strategy_rsp);
		free(order_rsp);
		free(pos_rsp);
		free(contr_rsp);
		return -1;
}

int 
sim_trader_destroy(sim_trader_t  *sim_data)
{
	free(contr_ar);
	free(g_all_contr);
	free(sim_data);
	return 0;
}