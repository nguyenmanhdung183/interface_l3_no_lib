static
gnb_return_et
gnb_il_parse_octet_string
(
    octet_string_t * p_octet_string,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
    SInt32 length_read = 0;
    *p_length_read = 0;

    memset(p_octet_string, 0, sizeof(octet_string_t));

    /* This function parses octet_string */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing octet_string");


/*----> UInt8 ~ length_a <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt8(&p_octet_string->length_a, p_src + *p_length_read, "length_a");
    *p_length_read += sizeof(p_octet_string->length_a);
    



        
        
    
        
                
        
 
    /* Check for correct range [B - both higher and lower boundary] */
    if(p_octet_string->length_a < 0 || p_octet_string->length_a > MAX_OCTET_STRING_LEN) 
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_octet_string->length_a should be in range [ 0 - MAX_OCTET_STRING_LEN]"
            "Incorrect value: %d", p_octet_string->length_a);
        return GNB_FAILURE;

    }


/*----> UInt16 ~ data_a <----*/ 






        
    /* Parse OCTET_STRING VARIABLE of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < p_octet_string->length_a; loop++)
        {
            gnb_cp_unpack_UInt16((void*)(&p_octet_string->data_a[loop]), (void*)(p_src + *p_length_read), "data_a[]");
            *p_length_read += sizeof(UInt16);
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



