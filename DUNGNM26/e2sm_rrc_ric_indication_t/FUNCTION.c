gnb_return_et
gnb_xxx_il_send_yyyy_e2sm_rrc_ric_indication 
(
    e2sm_rrc_ric_indication_t * p_e2sm_rrc_ric_indication,
    UInt16 src_module_id, /* Source module ID */
    UInt16 dest_module_id, /* Destination module ID */
    UInt16 transaction_id, /* Transaction ID */
    cell_index_t cell_index, /* Cell index */
    pup_send_callback send_callback
)
{
	    UInt16 msg_length, msg_api_length;
	    UInt8 *p_msg, *p_xxx_msg;
	
	    GNB_ASSERT(p_e2sm_rrc_ric_indication != GNB_PNULL);
	
	    SET_CELL_INDEX(cell_index);
	
	    /* Get API length */
	    msg_length = gnb_il_get_e2sm_rrc_ric_indication_len(p_e2sm_rrc_ric_indication);
	
	    if (msg_length == GNB_FAILURE)
	    {
		        GNB_LOG_ERROR("Failed to get message length for e2sm_rrc_ric_indication");
		        return GNB_FAILURE;
	    }
	
	    GNB_CP_TRACE(GNB_INFO, "Src(%u)->Dst(%u):E2SM_RRC_RIC_INDICATION", src_module_id, dest_module_id);
	
	
	    msg_appi_length = msg_length + GNB_API_HEADER_SIZE + GNB_INTERFACE_API_HEADER_SIZE;
	
	    /*Alloc buffer*/
	    p_msg = gnb_msg_mem_get(msg_appi_length);
	    if (p_msg == GNB_PNULL)
	    {
		        GNB_LOG_ERROR("Failed to allocate memory for e2sm_rrc_ric_indication message");
		        return GNB_FAILURE;
	    }
	
	    memset_wrapper(p_msg, 0, msg_appi_length);
	    p_xxx_msg = p_msg;
	
	    /* fill cspl header */
	    gnb_construct_api_header(p_xxx_msg, GNB_VERSION_ID, src_module_id, dest_module_id, E2SM_RRC_RIC_INDICATION, msg_api_length);
	
	    /*fill interface header */
	    p_xxx_msg += GNB_API_HEADER_SIZE;
	    gnb_construct_interface_api_header(p_xxx_msg, transaction_id, src_module_id, 
	        dest_module_id, E2SM_RRC_RIC_INDICATION, msg_length, cell_index);
	
	    /* fill message body */
	    p_xxx_msg += GNB_INTERFACE_API_HEADER_SIZE;
	    if (GNB_FAILURE == gnb_il_compose_e2sm_rrc_ric_indication(&p_xxx_msg, p_e2sm_rrc_ric_indication))
	    {
		        GNB_LOG_ERROR("Failed to compose e2sm_rrc_ric_indication message");
		        gnb_msg_mem_free(p_msg);
		        return GNB_FAILURE;
	    }
	
	    if (p_xxx_msg - msg_api_length != p_msg)
	    {
		        GNB_LOG_ERROR("Message length mismatch for e2sm_rrc_ric_indication: expected %u, actual %u", msg_api_length, (UInt16)(p_xxx_msg - p_msg));
		        gnb_msg_mem_free(p_msg);
		        return GNB_FAILURE;
	    }
	
	    /* Send message */
	    send_callback(p_msg, dst_module_id);
	
	    return GNB_SUCCESS;
}
