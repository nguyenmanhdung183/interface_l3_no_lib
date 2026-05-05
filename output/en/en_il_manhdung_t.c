/* get length */
static
gnb_length_t
gnb_il_get_manhdung_len 
(
    manhdung_t * p_manhdung
){
    gnb_length_t length = 0;
    GNB_ASSERT(p_manhdung != GNB_P_NULL);

/*----> UInt16 ~ numbits <----*/ 





    /* Get length of parameter of basic type */
    length += (gnb_length_t)sizeof(p_manhdung->numbits);



        
        
    
        
                
        


/*----> UInt8 ~ data <----*/ 








        
    /* Get length of OCTET_STRING VARIABLE of basic type elements */
    length += (p_manhdung->numbits * sizeof(p_manhdung->data[0]));
        
    
        
                
        



    return length;
}


/* compose */
static
gnb_return_et
gnb_il_compose_manhdung
(
    UInt8 **pp_buffer,
    manhdung_t * p_manhdung
){
    GNB_ASSERT(pp_buffer != GNB_P_NULL);
    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
    GNB_ASSERT(p_manhdung != GNB_P_NULL);

    /* This function composes manhdung */
    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing manhdung");

/*----> UInt16 ~ numbits <----*/ 





    /* Compose parameter of basic type */
    gnb_cp_pack_UInt16(*pp_buffer, &p_manhdung->numbits, "numbits");
    *pp_buffer += sizeof(p_manhdung->numbits);



        
        
    
        
        
        


/*----> UInt8 ~ data <----*/ 








        
    /* Compose OCTET_STRING VARIABLE of basic type elements */
    {
        gnb_counter_t loop;
        for(loop = 0; loop < p_manhdung->numbits; loop++)
        {
            gnb_cp_pack_UInt8(*pp_buffer, &p_manhdung->data[loop], "data[]");
            *pp_buffer += sizeof(UInt8);
        }
    }
        
    
        
        
        



    return GNB_SUCCESS;
}



