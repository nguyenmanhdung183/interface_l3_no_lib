
#include <stdio.h>

void trace_rrc_e2sm_kpm_ric_sub_req_t(rrc_e2sm_kpm_ric_sub_req_t *p_rrc_e2sm_kpm_ric_sub_req)
{
	    	fprintf(stderr, "\n[TRACE] ===== rrc_e2sm_kpm_ric_sub_req_t =====\n");
	    	fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->bitmask = %u\n", p_rrc_e2sm_kpm_ric_sub_req->bitmask);
	    	fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->ric_request_id = %u\n", p_rrc_e2sm_kpm_ric_sub_req->ric_request_id);
	    	fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->periodic = %u\n", p_rrc_e2sm_kpm_ric_sub_req->periodic);
	    	fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->report_period_ms = %u\n", p_rrc_e2sm_kpm_ric_sub_req->report_period_ms);
	    	if (p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.bitmask & SUB_RIC_MOBILITY_REPORT_PRESENT)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== e2_report_mobility_req_t =====\n");
		    		fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_attempt = %u\n", p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_attempt);
		    		fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_succ = %u\n", p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_succ);
		    		fprintf(stderr, "[TRACE] p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_failure = %u\n", p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_failure);
	    	}
}
