
xnap_return_et assign_hardcode_value_e2sm_rrc_ric_indication_t( e2sm_rrc_ric_indication_t *p_e2sm_rrc_ric_indication )
{
	    		p_e2sm_rrc_ric_indication->bitmask = 0;
	    		p_e2sm_rrc_ric_indication->ric_request_id = 0;
	    		#if 1 /*idx5: report_mobility_ind - STRUCT - N --> S */
	    			p_e2sm_rrc_ric_indication->report_mobility_ind.bitmask |= IND_RIC_MOBILITY_REPORT_PRESENT
	    			{
		    			p_e2sm_rrc_ric_indication->report_mobility_ind.ho_attempt = 0;
		    			p_e2sm_rrc_ric_indication->report_mobility_ind.ho_succ = 0;
		    			p_e2sm_rrc_ric_indication->report_mobility_ind.ho_failure = 0;
	    			}
	    		#endif /* idx5: report_mobility_ind E */
	
	    return XNAP_SUCCESS;
}
