/* get length */
static
gnb_length_t
gnb_il_get_TEST_PRINT_len 
(
    TEST_PRINT_t * p_TEST_PRINT
){
    gnb_length_t length = 0;
    GNB_ASSERT(p_TEST_PRINT != GNB_P_NULL);

/*----> UInt8 ~ data <----*/ 





    /* Get length of parameter of basic type */
    length += (gnb_length_t)sizeof(p_TEST_PRINT->data);



        
        
    
        
                
        



    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_TEST_PRINT
(
    UInt8 **pp_buffer,
    TEST_PRINT_t * p_TEST_PRINT
){
    GNB_ASSERT(pp_buffer != GNB_P_NULL);
    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
    GNB_ASSERT(p_TEST_PRINT != GNB_P_NULL);

    /* This function composes TEST_PRINT */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing TEST_PRINT");

/*----> UInt8 ~ data <----*/ 





    /* Compose parameter of basic type */
    gnb_cp_pack_UInt8(*pp_buffer, &p_TEST_PRINT->data, "data");
    *pp_buffer += sizeof(p_TEST_PRINT->data);



        
        
    
        
        
        



    return GNB_SUCCESS;
}



