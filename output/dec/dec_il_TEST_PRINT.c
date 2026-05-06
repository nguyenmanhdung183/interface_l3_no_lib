static
gnb_return_et
gnb_il_parse_TEST_PRINT
(
    TEST_PRINT_t * p_TEST_PRINT,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
    SInt32 length_read = 0;
    *p_length_read = 0;

    memset(p_TEST_PRINT, 0, sizeof(TEST_PRINT_t));

    /* This function parses TEST_PRINT */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing TEST_PRINT");


/*----> UInt8 ~ data <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt8(&p_TEST_PRINT->data, p_src + *p_length_read, "data");
    *p_length_read += sizeof(p_TEST_PRINT->data);
    



        
        
    
        
                
        
 



/* final check */
    if(*p_length_read > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }

    return GNB_SUCCESS;
}



