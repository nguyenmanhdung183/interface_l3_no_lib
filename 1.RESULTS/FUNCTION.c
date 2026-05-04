gnb_return_et
gnb_xxx_il_send_yyyy_device_config 
(
    device_config_t * p_device_config,
    UInt16 src_module_id, /* Source module ID */
    UInt16 dest_module_id, /* Destination module ID */
    UInt16 transaction_id, /* Transaction ID */
    cell_index_t cell_index, /* Cell index */
    pup_send_callback send_callback
)
{
	    UInt16 msg_length, msg_api_length;
	    UInt8 *p_msg, *p_xxx_msg;
	
	    GNB_ASSERT(p_device_config != GNB_PNULL);
	
	    SET_CELL_INDEX(cell_index);
	
	    /* Get API length */
	    msg_length = gnb_il_get_device_config_len(p_device_config);
	
	    if (msg_length == GNB_FAILURE)
	    {
		        GNB_LOG_ERROR("Failed to get message length for device_config");
		        return GNB_FAILURE;
	    }
	
	    GNB_CP_TRACE(GNB_INFO, "Src(%u)->Dst(%u):DEVICE_CONFIG", src_module_id, dest_module_id);
	
	
	    msg_api_length = msg_length + GNB_API_HEADER_SIZE + GNB_INTERFACE_API_HEADER_SIZE;
	
	    /*Alloc buffer*/
	    p_msg = gnb_msg_mem_get(msg_api_length);
	    if (p_msg == GNB_PNULL)
	    {
		        GNB_LOG_ERROR("Failed to allocate memory for device_config message");
		        return GNB_FAILURE;
	    }
	
	    memset_wrapper(p_msg, 0, msg_api_length);
	    p_xxx_msg = p_msg;
	
	    /* fill cspl header */
	    gnb_construct_api_header(p_xxx_msg, GNB_VERSION_ID, src_module_id, dest_module_id, DEVICE_CONFIG, msg_api_length);
	
	    /*fill interface header */
	    p_xxx_msg += GNB_API_HEADER_SIZE;
	    gnb_construct_interface_api_header(p_xxx_msg, transaction_id, src_module_id, 
	        dest_module_id, DEVICE_CONFIG, msg_length, cell_index);
	
	    /* fill message body */
	    p_xxx_msg += GNB_INTERFACE_API_HEADER_SIZE;
	    if (GNB_FAILURE == gnb_il_compose_device_config(&p_xxx_msg, p_device_config))
	    {
		        GNB_LOG_ERROR("Failed to compose device_config message");
		        gnb_msg_mem_free(p_msg);
		        return GNB_FAILURE;
	    }
	
	    if (p_xxx_msg - msg_api_length != p_msg)
	    {
		        GNB_LOG_ERROR("Message length mismatch for device_config: expected %u, actual %u", msg_api_length, (UInt16)(p_xxx_msg - p_msg));
		        gnb_msg_mem_free(p_msg);
		        return GNB_FAILURE;
	    }
	
	    /* Send message */
	    send_callback(p_msg, dst_module_id);
	
	    return GNB_SUCCESS;
}
