static
gnb_return_et
gnb_il_parse_plmn_id
(
    plmn_id_t * p_plmn_id,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
    SInt32 length_read = 0;
    *p_length_read = 0;

    memset(p_plmn_id, 0, sizeof(plmn_id_t));

    /* This function parses plmn_id */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing plmn_id");


/*----> UInt8 ~ plmn_count <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt8(&p_plmn_id->plmn_count, p_src + *p_length_read, "plmn_count");
    *p_length_read += sizeof(p_plmn_id->plmn_count);
    



        
        
    
        
                
        
 
    /* Check for correct range [B - both higher and lower boundary] */
    if(p_plmn_id->plmn_count < 0 || p_plmn_id->plmn_count > MAX_OCTET_STRING_LEN) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_plmn_id->plmn_count should be in range [ 0 - MAX_OCTET_STRING_LEN]"
            "Incorrect value: %d", p_plmn_id->plmn_count);
        return GNB_FAILURE;

    }


/*----> UInt8 ~ data <----*/ 






        
    /* Parse OCTET_STRING VARIABLE of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < p_plmn_id->plmn_count; loop++)
        {
            gnb_cp_unpack_UInt8((void*)(&p_plmn_id->data[loop]), (void*)(p_src + *p_length_read), "data[]");
            *p_length_read += sizeof(UInt8);
        }
    }
        
    
        
                
        
 



/* final check */
    if(*p_length_read > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }

    return GNB_SUCCESS;
}



