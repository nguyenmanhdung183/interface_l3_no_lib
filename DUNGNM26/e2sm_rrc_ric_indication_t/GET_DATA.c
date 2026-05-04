
#include <stdio.h>

void trace_e2sm_rrc_ric_indication_t(e2sm_rrc_ric_indication_t *p_e2sm_rrc_ric_indication)
{
	    	fprintf(stderr, "\n[TRACE] ===== e2sm_rrc_ric_indication_t =====\n");
	    	fprintf(stderr, "[TRACE] p_e2sm_rrc_ric_indication->bitmask = %u\n", p_e2sm_rrc_ric_indication->bitmask);
	    	fprintf(stderr, "[TRACE] p_e2sm_rrc_ric_indication->ric_request_id = %u\n", p_e2sm_rrc_ric_indication->ric_request_id);
	    	if (p_e2sm_rrc_ric_indication->report_mobility_ind.bitmask & IND_RIC_MOBILITY_REPORT_PRESENT)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== e2_report_mobility_ind_t =====\n");
		    		fprintf(stderr, "[TRACE] p_e2sm_rrc_ric_indication->report_mobility_ind.ho_attempt = %u\n", p_e2sm_rrc_ric_indication->report_mobility_ind.ho_attempt);
		    		fprintf(stderr, "[TRACE] p_e2sm_rrc_ric_indication->report_mobility_ind.ho_succ = %u\n", p_e2sm_rrc_ric_indication->report_mobility_ind.ho_succ);
		    		fprintf(stderr, "[TRACE] p_e2sm_rrc_ric_indication->report_mobility_ind.ho_failure = %u\n", p_e2sm_rrc_ric_indication->report_mobility_ind.ho_failure);
	    	}
}
