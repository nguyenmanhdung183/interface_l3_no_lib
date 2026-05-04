static
gnb_return_et
gnb_il_parse_e2_report_mobility_ind
(
    e2_report_mobility_ind_t * p_e2_report_mobility_ind,
    UInt8 * p_src,
    UInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;
	
	    memset(p_e2_report_mobility_ind, 0, sizeof(e2_report_mobility_ind_t));
	
	    /* This function parses e2_report_mobility_ind */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing e2_report_mobility_ind");
	
	
	/*----> UInt32 ~ ho_attempt <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt32) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt32(&p_e2_report_mobility_ind->ho_attempt, p_src + *p_length_read, "ho_attempt");
	    *p_length_read += sizeof(p_e2_report_mobility_ind->ho_attempt);
	    
	
	/*----> UInt32 ~ ho_succ <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt32) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt32(&p_e2_report_mobility_ind->ho_succ, p_src + *p_length_read, "ho_succ");
	    *p_length_read += sizeof(p_e2_report_mobility_ind->ho_succ);
	    
	
	/*----> UInt32 ~ ho_failure <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt32) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt32(&p_e2_report_mobility_ind->ho_failure, p_src + *p_length_read, "ho_failure");
	    *p_length_read += sizeof(p_e2_report_mobility_ind->ho_failure);
	    
	
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
gnb_il_parse_e2sm_rrc_ric_indication
(
    e2sm_rrc_ric_indication_t * p_e2sm_rrc_ric_indication,
    UInt8 * p_src,
    UInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;
	
	    memset(p_e2sm_rrc_ric_indication, 0, sizeof(e2sm_rrc_ric_indication_t));
	
	    /* This function parses e2sm_rrc_ric_indication */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing e2sm_rrc_ric_indication");
	
	
	/*----> UInt16 ~ bitmask <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_e2sm_rrc_ric_indication->bitmask, p_src + *p_length_read, "bitmask");
	    *p_length_read += sizeof(p_e2sm_rrc_ric_indication->bitmask);
	    
	
	/*----> UInt32 ~ ric_request_id <----*/ 
	    if (*p_length_read + (SInt32)sizeof(UInt32) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt32(&p_e2sm_rrc_ric_indication->ric_request_id, p_src + *p_length_read, "ric_request_id");
	    *p_length_read += sizeof(p_e2sm_rrc_ric_indication->ric_request_id);
	    
	
	/*----> e2_report_mobility_ind_t ~ report_mobility_ind <----*/ 
	    /* Optional element */
	    if(p_e2sm_rrc_ric_indication->bitmask & IND_RIC_MOBILITY_REPORT_PRESENT)
	    {
		    /* Parse/Unpack IE */
		    if(GNB_FAILURE == gnb_il_parse_e2_report_mobility_ind(
		        &p_e2sm_rrc_ric_indication->report_mobility_ind, 
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


