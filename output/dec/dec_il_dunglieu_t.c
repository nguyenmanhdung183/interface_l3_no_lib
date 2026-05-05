static
gnb_return_et
gnb_il_parse_dunglieu
(
    dunglieu_t * p_dunglieu,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
    SInt32 length_read = 0;
    *p_length_read = 0;

    memset(p_dunglieu, 0, sizeof(dunglieu_t));

    /* This function parses dunglieu */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing dunglieu");


/*----> UInt8 ~ haha <----*/ 






        
        
    
        
    /* Parse of OCTET_STRING FIXED of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < ARRSIZE(p_dunglieu->haha); loop++)
        {
            gnb_cp_unpack_UInt8((void*)(&p_dunglieu->haha[loop]), (void*)(p_src + *p_length_read), "haha[]");
            *p_length_read += sizeof(UInt8);
        }
    }
                
        
 



/*----> UInt16 ~ hihi <----*/ 



    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }
    /* Parse/Unpack parameter of basic type */
    gnb_cp_unpack_UInt16(&p_dunglieu->hihi, p_src + *p_length_read, "hihi");
    *p_length_read += sizeof(p_dunglieu->hihi);
    



        
        
    
        
                
        
 



/* final check */
    if(*p_length_read > length_left)
    {
        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
        return GNB_FAILURE;
    }

    return GNB_SUCCESS;
}



