static
gnb_return_et
gnb_il_parse_manhdung
(
    manhdung_t * p_manhdung,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
    SInt32 length_read = 0;
    *p_length_read = 0;

    memset(p_manhdung, 0, sizeof(manhdung_t));

    /* This function parses manhdung */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing manhdung");


/*----> UInt16 ~ numbits <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt16(&p_manhdung->numbits, p_src + *p_length_read, "numbits");
    *p_length_read += sizeof(p_manhdung->numbits);
    



        
        
    
        
                
        
 



/*----> UInt8 ~ data <----*/ 






        
    /* Parse OCTET_STRING VARIABLE of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < p_manhdung->numbits; loop++)
        {
            gnb_cp_unpack_UInt8((void*)(&p_manhdung->data[loop]), (void*)(p_src + *p_length_read), "data[]");
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



