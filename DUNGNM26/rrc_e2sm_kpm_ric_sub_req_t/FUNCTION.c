gnb_return_et
gnb_xxx_il_send_yyyy_rrc_e2sm_kpm_ric_sub_req 
(
    rrc_e2sm_kpm_ric_sub_req_t * p_rrc_e2sm_kpm_ric_sub_req,
    UInt16 src_module_id, /* Source module ID */
    UInt16 dest_module_id, /* Destination module ID */
    UInt16 transaction_id, /* Transaction ID */
    cell_index_t cell_index, /* Cell index */
    pup_send_callback send_callback
)
{
	    UInt16 msg_length, msg_api_length;
	    UInt8 *p_msg, *p_xxx_msg;
	
	    GNB_ASSERT(p_rrc_e2sm_kpm_ric_sub_req != GNB_PNULL);
	
	    SET_CELL_INDEX(cell_index);
	
	    /* Get API length */
	    msg_length = gnb_il_get_rrc_e2sm_kpm_ric_sub_req_len(p_rrc_e2sm_kpm_ric_sub_req);
	
	    if (msg_length == GNB_FAILURE)
	    {
		        GNB_LOG_ERROR("Failed to get message length for rrc_e2sm_kpm_ric_sub_req");
		        return GNB_FAILURE;
	    }
	
	    GNB_CP_TRACE(GNB_INFO, "Src(%u)->Dst(%u):RRC_E2SM_KPM_RIC_SUB_REQ", src_module_id, dest_module_id);
	
	
	    msg_appi_length = msg_length + GNB_API_HEADER_SIZE + GNB_INTERFACE_API_HEADER_SIZE;
	
	    /*Alloc buffer*/
	    p_msg = gnb_msg_mem_get(msg_appi_length);
	    if (p_msg == GNB_PNULL)
	    {
		        GNB_LOG_ERROR("Failed to allocate memory for rrc_e2sm_kpm_ric_sub_req message");
		        return GNB_FAILURE;
	    }
	
	    memset_wrapper(p_msg, 0, msg_appi_length);
	    p_xxx_msg = p_msg;
	
	    /* fill cspl header */
	    gnb_construct_api_header(p_xxx_msg, GNB_VERSION_ID, src_module_id, dest_module_id, RRC_E2SM_KPM_RIC_SUB_REQ, msg_api_length);
	
	    /*fill interface header */
	    p_xxx_msg += GNB_API_HEADER_SIZE;
	    gnb_construct_interface_api_header(p_xxx_msg, transaction_id, src_module_id, 
	        dest_module_id, RRC_E2SM_KPM_RIC_SUB_REQ, msg_length, cell_index);
	
	    /* fill message body */
	    p_xxx_msg += GNB_INTERFACE_API_HEADER_SIZE;
	    if (GNB_FAILURE == gnb_il_compose_rrc_e2sm_kpm_ric_sub_req(&p_xxx_msg, p_rrc_e2sm_kpm_ric_sub_req))
	    {
		        GNB_LOG_ERROR("Failed to compose rrc_e2sm_kpm_ric_sub_req message");
		        gnb_msg_mem_free(p_msg);
		        return GNB_FAILURE;
	    }
	
	    if (p_xxx_msg - msg_api_length != p_msg)
	    {
		        GNB_LOG_ERROR("Message length mismatch for rrc_e2sm_kpm_ric_sub_req: expected %u, actual %u", msg_api_length, (UInt16)(p_xxx_msg - p_msg));
		        gnb_msg_mem_free(p_msg);
		        return GNB_FAILURE;
	    }
	
	    /* Send message */
	    send_callback(p_msg, dst_module_id);
	
	    return GNB_SUCCESS;
}
