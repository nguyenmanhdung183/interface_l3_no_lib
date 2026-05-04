
xnap_return_et assign_hardcode_value_rrc_e2sm_kpm_ric_sub_req_t( rrc_e2sm_kpm_ric_sub_req_t *p_rrc_e2sm_kpm_ric_sub_req )
{
	    		p_rrc_e2sm_kpm_ric_sub_req->bitmask = 0;
	    		p_rrc_e2sm_kpm_ric_sub_req->ric_request_id = 0;
	    		p_rrc_e2sm_kpm_ric_sub_req->periodic = 0;
	    		p_rrc_e2sm_kpm_ric_sub_req->report_period_ms = 0;
	    		#if 1 /*idx9: report_mobility_req - STRUCT - N --> S */
	    			p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.bitmask |= SUB_RIC_MOBILITY_REPORT_PRESENT
	    			{
		    			p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_attempt = 0;
		    			p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_succ = 0;
		    			p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req.is_ho_failure = 0;
	    			}
	    		#endif /* idx9: report_mobility_req E */
	
	    return XNAP_SUCCESS;
}
