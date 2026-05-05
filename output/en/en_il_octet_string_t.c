/* get length */
static
gnb_length_t
gnb_il_get_octet_string_len 
(
    octet_string_t * p_octet_string
){
    gnb_length_t length = 0;
    GNB_ASSERT(p_octet_string != GNB_P_NULL);

/*----> UInt8 ~ length_a <----*/ 



    /* Check for correct range [B - both higher and lower boundary] */
    if(p_octet_string->length_a < 0 || p_octet_string->length_a > MAX_OCTET_STRING_LEN) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_octet_string->length_a should be in range [ 0 - MAX_OCTET_STRING_LEN]"
            "Incorrect value: %d", p_octet_string->length_a);
        return GNB_FAILURE;

    }

    /* Get length of parameter of basic type */
    length += (gnb_length_t)sizeof(p_octet_string->length_a);



        
        
    
        
                
        


/*----> UInt16 ~ data_a <----*/ 








        
    /* Get length of OCTET_STRING VARIABLE of basic type elements */
    length += (p_octet_string->length_a * sizeof(p_octet_string->data_a[0]));
        
    
        
                
        



    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_octet_string
(
    UInt8 **pp_buffer,
    octet_string_t * p_octet_string
){
    GNB_ASSERT(pp_buffer != GNB_P_NULL);
    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
    GNB_ASSERT(p_octet_string != GNB_P_NULL);

    /* This function composes octet_string */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing octet_string");

/*----> UInt8 ~ length_a <----*/ 



    /* Check for correct range [B - both higher and lower boundary] */
    if(p_octet_string->length_a < 0 || p_octet_string->length_a > MAX_OCTET_STRING_LEN) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_octet_string->length_a should be in range [ 0 - MAX_OCTET_STRING_LEN]"
            "Incorrect value: %d", p_octet_string->length_a);
        return GNB_FAILURE;

    }

    /* Compose parameter of basic type */
    gnb_cp_pack_UInt8(*pp_buffer, &p_octet_string->length_a, "length_a");
    *pp_buffer += sizeof(p_octet_string->length_a);



        
        
    
        
        
        


/*----> UInt16 ~ data_a <----*/ 








        
    /* Compose OCTET_STRING VARIABLE of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < p_octet_string->length_a; loop++)
        {
            gnb_cp_pack_UInt16(*pp_buffer, &p_octet_string->data_a[loop], "data_a[]");
            *pp_buffer += sizeof(UInt16);
        }
    }
        
    
        
        
        



    return GNB_SUCCESS;
}



