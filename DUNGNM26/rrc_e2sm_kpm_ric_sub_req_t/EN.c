/* get length */
static
gnb_length_t
gnb_il_get_e2_report_mobility_req_len 
(
    e2_report_mobility_req_t * p_e2_report_mobility_req
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_e2_report_mobility_req != GNB_P_NULL);
	
	/*----> UInt8 ~ is_ho_attempt <----*/ 
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_attempt < 0.0 || p_e2_report_mobility_req->is_ho_attempt > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_attempt should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_attempt);
		        return GNB_FAILURE;
	    }
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_e2_report_mobility_req->is_ho_attempt);
	
	/*----> UInt8 ~ is_ho_succ <----*/ 
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_succ < 0.0 || p_e2_report_mobility_req->is_ho_succ > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_succ should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_succ);
		        return GNB_FAILURE;
	    }
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_e2_report_mobility_req->is_ho_succ);
	
	/*----> UInt8 ~ is_ho_failure <----*/ 
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_failure < 0.0 || p_e2_report_mobility_req->is_ho_failure > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_failure should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_failure);
		        return GNB_FAILURE;
	    }
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_e2_report_mobility_req->is_ho_failure);
	
	
	    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_e2_report_mobility_req
(
    UInt8 **pp_buffer,
    e2_report_mobility_req_t * p_e2_report_mobility_req
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_e2_report_mobility_req != GNB_P_NULL);
	
	    /* This function composes e2_report_mobility_req */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing e2_report_mobility_req");
	
	/*----> UInt8 ~ is_ho_attempt <----*/ 
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_attempt < 0.0 || p_e2_report_mobility_req->is_ho_attempt > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_attempt should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_attempt);
		        return GNB_FAILURE;
	    }
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_e2_report_mobility_req->is_ho_attempt, "is_ho_attempt");
	    *pp_buffer += sizeof(p_e2_report_mobility_req->is_ho_attempt);
	
	/*----> UInt8 ~ is_ho_succ <----*/ 
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_succ < 0.0 || p_e2_report_mobility_req->is_ho_succ > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_succ should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_succ);
		        return GNB_FAILURE;
	    }
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_e2_report_mobility_req->is_ho_succ, "is_ho_succ");
	    *pp_buffer += sizeof(p_e2_report_mobility_req->is_ho_succ);
	
	/*----> UInt8 ~ is_ho_failure <----*/ 
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_failure < 0.0 || p_e2_report_mobility_req->is_ho_failure > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_failure should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_failure);
		        return GNB_FAILURE;
	    }
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_e2_report_mobility_req->is_ho_failure, "is_ho_failure");
	    *pp_buffer += sizeof(p_e2_report_mobility_req->is_ho_failure);
	
	
	    return GNG_SUCCESS;
}


/* get length */
static
gnb_length_t
gnb_il_get_rrc_e2sm_kpm_ric_sub_req_len 
(
    rrc_e2sm_kpm_ric_sub_req_t * p_rrc_e2sm_kpm_ric_sub_req
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_rrc_e2sm_kpm_ric_sub_req != GNB_P_NULL);
	
	/*----> UInt16 ~ bitmask <----*/ 
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rrc_e2sm_kpm_ric_sub_req->bitmask);
	
	/*----> UInt32 ~ ric_request_id <----*/ 
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rrc_e2sm_kpm_ric_sub_req->ric_request_id);
	
	/*----> UInt8 ~ periodic <----*/ 
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rrc_e2sm_kpm_ric_sub_req->periodic);
	
	/*----> UInt32 ~ report_period_ms <----*/ 
	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rrc_e2sm_kpm_ric_sub_req->report_period_ms);
	
	/*----> e2_report_mobility_req_t ~ report_mobility_req <----*/ 
	    /* Optional element */
	    if(p_rrc_e2sm_kpm_ric_sub_req->bitmask & SUB_RIC_MOBILITY_REPORT_PRESENT)
	    {
		    /* Get length of IE */
		    length += gnb_il_get_e2_report_mobility_req_len(&p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req);
	    }
	
	
	    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_rrc_e2sm_kpm_ric_sub_req
(
    UInt8 **pp_buffer,
    rrc_e2sm_kpm_ric_sub_req_t * p_rrc_e2sm_kpm_ric_sub_req
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_rrc_e2sm_kpm_ric_sub_req != GNB_P_NULL);
	
	    /* This function composes rrc_e2sm_kpm_ric_sub_req */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing rrc_e2sm_kpm_ric_sub_req");
	
	/*----> UInt16 ~ bitmask <----*/ 
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_rrc_e2sm_kpm_ric_sub_req->bitmask, "bitmask");
	    *pp_buffer += sizeof(p_rrc_e2sm_kpm_ric_sub_req->bitmask);
	
	/*----> UInt32 ~ ric_request_id <----*/ 
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt32(*pp_buffer, &p_rrc_e2sm_kpm_ric_sub_req->ric_request_id, "ric_request_id");
	    *pp_buffer += sizeof(p_rrc_e2sm_kpm_ric_sub_req->ric_request_id);
	
	/*----> UInt8 ~ periodic <----*/ 
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_rrc_e2sm_kpm_ric_sub_req->periodic, "periodic");
	    *pp_buffer += sizeof(p_rrc_e2sm_kpm_ric_sub_req->periodic);
	
	/*----> UInt32 ~ report_period_ms <----*/ 
	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt32(*pp_buffer, &p_rrc_e2sm_kpm_ric_sub_req->report_period_ms, "report_period_ms");
	    *pp_buffer += sizeof(p_rrc_e2sm_kpm_ric_sub_req->report_period_ms);
	
	/*----> e2_report_mobility_req_t ~ report_mobility_req <----*/ 
	    /* Optional element */
	    if(p_rrc_e2sm_kpm_ric_sub_req->bitmask & SUB_RIC_MOBILITY_REPORT_PRESENT)
	    {
		    /* Compose IE */
		    if(GNB_FAILURE == gnb_il_compose_e2_report_mobility_req(pp_buffer, &p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req))
		    {
			        return GNB_FAILURE;
		    }
	    }
	
	
	    return GNG_SUCCESS;
}


