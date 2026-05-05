/* get length */
static
gnb_length_t
gnb_il_get_dunglieu_len 
(
    dunglieu_t * p_dunglieu
){
    gnb_length_t length = 0;
    GNB_ASSERT(p_dunglieu != GNB_P_NULL);

/*----> UInt8 ~ haha <----*/ 








        
        
    
        
    /* Get length of OCTET_STRING FIXED of basic type elements */
    length += sizeof(p_dunglieu->haha);
                
        


/*----> UInt16 ~ hihi <----*/ 





    /* Get length of parameter of basic type */
    length += (gnb_length_t)sizeof(p_dunglieu->hihi);



        
        
    
        
                
        



    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_dunglieu
(
    UInt8 **pp_buffer,
    dunglieu_t * p_dunglieu
){
    GNB_ASSERT(pp_buffer != GNB_P_NULL);
    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
    GNB_ASSERT(p_dunglieu != GNB_P_NULL);

    /* This function composes dunglieu */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing dunglieu");

/*----> UInt8 ~ haha <----*/ 








        
        
    
        
    /* Compose of OCTET_STRING FIXED of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < ARRSIZE(p_dunglieu->haha); loop++)
        {
            gnb_cp_pack_UInt8(*pp_buffer, &p_dunglieu->haha[loop], "haha[]");
            *pp_buffer += sizeof(UInt8);
        }
    }
        
        


/*----> UInt16 ~ hihi <----*/ 





    /* Compose parameter of basic type */
    gnb_cp_pack_UInt16(*pp_buffer, &p_dunglieu->hihi, "hihi");
    *pp_buffer += sizeof(p_dunglieu->hihi);



        
        
    
        
        
        



    return GNG_SUCCESS;
}



