static
gnb_return_et
gnb_il_parse_e2_report_mobility_req
(
    e2_report_mobility_req_t * p_e2_report_mobility_req,
    UInt8 * p_src,
    UInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;
	
	    memset(p_e2_report_mobility_req, 0, sizeof(e2_report_mobility_req_t));
	
	    /* This function parses e2_report_mobility_req */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing e2_report_mobility_req");
	
	
	/*----> UInt8 ~ is_ho_attempt <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_e2_report_mobility_req->is_ho_attempt, p_src + *p_length_read, "is_ho_attempt");
	    *p_length_read += sizeof(p_e2_report_mobility_req->is_ho_attempt);
	    
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_attempt < 0.0 || p_e2_report_mobility_req->is_ho_attempt > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_attempt should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_attempt);
		        return GNB_FAILURE;
	    }
	
	/*----> UInt8 ~ is_ho_succ <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_e2_report_mobility_req->is_ho_succ, p_src + *p_length_read, "is_ho_succ");
	    *p_length_read += sizeof(p_e2_report_mobility_req->is_ho_succ);
	    
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_succ < 0.0 || p_e2_report_mobility_req->is_ho_succ > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_succ should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_succ);
		        return GNB_FAILURE;
	    }
	
	/*----> UInt8 ~ is_ho_failure <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_e2_report_mobility_req->is_ho_failure, p_src + *p_length_read, "is_ho_failure");
	    *p_length_read += sizeof(p_e2_report_mobility_req->is_ho_failure);
	    
	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_e2_report_mobility_req->is_ho_failure < 0.0 || p_e2_report_mobility_req->is_ho_failure > 1.0) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_e2_report_mobility_req->is_ho_failure should be in range [ 0.0 - 1.0]"
		            "Incorrect value: %d", p_e2_report_mobility_req->is_ho_failure);
		        return GNB_FAILURE;
	    }
	
	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	
	    return GNG_SUCCESS;
}


static
gnb_return_et
gnb_il_parse_rrc_e2sm_kpm_ric_sub_req
(
    rrc_e2sm_kpm_ric_sub_req_t * p_rrc_e2sm_kpm_ric_sub_req,
    UInt8 * p_src,
    UInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;
	
	    memset(p_rrc_e2sm_kpm_ric_sub_req, 0, sizeof(rrc_e2sm_kpm_ric_sub_req_t));
	
	    /* This function parses rrc_e2sm_kpm_ric_sub_req */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing rrc_e2sm_kpm_ric_sub_req");
	
	
	/*----> UInt16 ~ bitmask <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_rrc_e2sm_kpm_ric_sub_req->bitmask, p_src + *p_length_read, "bitmask");
	    *p_length_read += sizeof(p_rrc_e2sm_kpm_ric_sub_req->bitmask);
	    
	
	/*----> UInt32 ~ ric_request_id <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt32) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt32(&p_rrc_e2sm_kpm_ric_sub_req->ric_request_id, p_src + *p_length_read, "ric_request_id");
	    *p_length_read += sizeof(p_rrc_e2sm_kpm_ric_sub_req->ric_request_id);
	    
	
	/*----> UInt8 ~ periodic <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_rrc_e2sm_kpm_ric_sub_req->periodic, p_src + *p_length_read, "periodic");
	    *p_length_read += sizeof(p_rrc_e2sm_kpm_ric_sub_req->periodic);
	    
	
	/*----> UInt32 ~ report_period_ms <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt32) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt32(&p_rrc_e2sm_kpm_ric_sub_req->report_period_ms, p_src + *p_length_read, "report_period_ms");
	    *p_length_read += sizeof(p_rrc_e2sm_kpm_ric_sub_req->report_period_ms);
	    
	
	/*----> e2_report_mobility_req_t ~ report_mobility_req <----*/ 
	    /* Optional element */
	    if(p_rrc_e2sm_kpm_ric_sub_req->bitmask & SUB_RIC_MOBILITY_REPORT_PRESENT)
	    {
		    /* Parse/Unpack IE */
		    if(GNB_FAILURE == gnb_il_parse_e2_report_mobility_req(
		        &p_rrc_e2sm_kpm_ric_sub_req->report_mobility_req, 
		        p_src + *p_length_read, 
		        length_left - *p_length_read,
		        &length_read))
		    {
			        return GNB_FAILURE;
		    }
		
		    *p_length_read += length_read;
	    }
	
	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	
	    return GNG_SUCCESS;
}


