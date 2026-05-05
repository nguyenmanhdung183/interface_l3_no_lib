/* get length */
static
gnb_length_t
gnb_il_get_plmn_id_len 
(
    plmn_id_t * p_plmn_id
){
    gnb_length_t length = 0;
    GNB_ASSERT(p_plmn_id != GNB_P_NULL);

/*----> UInt8 ~ plmn_count <----*/ 



    /* Check for correct range [B - both higher and lower boundary] */
    if(p_plmn_id->plmn_count < 0 || p_plmn_id->plmn_count > MAX_OCTET_STRING_LEN) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_plmn_id->plmn_count should be in range [ 0 - MAX_OCTET_STRING_LEN]"
            "Incorrect value: %d", p_plmn_id->plmn_count);
        return GNB_FAILURE;

    }

    /* Get length of parameter of basic type */
    length += (gnb_length_t)sizeof(p_plmn_id->plmn_count);



        
        
    
        
                
        


/*----> UInt8 ~ data <----*/ 








        
    /* Get length of OCTET_STRING VARIABLE of basic type elements */
    length += (p_plmn_id->plmn_count * sizeof(p_plmn_id->data[0]));
        
    
        
                
        



    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_plmn_id
(
    UInt8 **pp_buffer,
    plmn_id_t * p_plmn_id
){
    GNB_ASSERT(pp_buffer != GNB_P_NULL);
    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
    GNB_ASSERT(p_plmn_id != GNB_P_NULL);

    /* This function composes plmn_id */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing plmn_id");

/*----> UInt8 ~ plmn_count <----*/ 



    /* Check for correct range [B - both higher and lower boundary] */
    if(p_plmn_id->plmn_count < 0 || p_plmn_id->plmn_count > MAX_OCTET_STRING_LEN) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_plmn_id->plmn_count should be in range [ 0 - MAX_OCTET_STRING_LEN]"
            "Incorrect value: %d", p_plmn_id->plmn_count);
        return GNB_FAILURE;

    }

    /* Compose parameter of basic type */
    gnb_cp_pack_UInt8(*pp_buffer, &p_plmn_id->plmn_count, "plmn_count");
    *pp_buffer += sizeof(p_plmn_id->plmn_count);



        
        
    
        
        
        


/*----> UInt8 ~ data <----*/ 








        
    /* Compose OCTET_STRING VARIABLE of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < p_plmn_id->plmn_count; loop++)
        {
            gnb_cp_pack_UInt8(*pp_buffer, &p_plmn_id->data[loop], "data[]");
            *pp_buffer += sizeof(UInt8);
        }
    }
        
    
        
        
        



    return GNB_SUCCESS;
}



