#ifndef __MODULATION_DEFS__H__
#define __MODULATION_DEFS__H__
/** @addtogroup _PHY_MODULATION_
 * @{
*/

/**
\fn void PHY_ofdm_mod(int *input,int *output,unsigned char log2fftsize,unsigned char nb_symbols,unsigned short nb_prefix_samples,short *twiddle_ifft,unsigned short *rev,Extension_t etype)
This function performs OFDM modulation with cyclic extension or zero-padding.

@param input The sequence input samples in the frequency-domain.  This is a concatenation of the input symbols in SIMD redundant format
@param output The time-domain output signal
@param log2fftsize Base-2 logarithm of the OFDM symbol size (\f$N_d\f$)
@param nb_symbols The number of OFDM symbols in the block
@param nb_prefix_samples The number of prefix/suffix/zero samples
@param twiddle_ifft Pointer to the ifft twiddle factors
@param rev Pointer to the bit-reversal permutation
@param etype Type of extension (CYCLIC_PREFIX,CYCLIC_SUFFIX,ZEROS)

*/
void PHY_ofdm_mod(int *input,           
	          int *output,          
	          unsigned char log2fftsize,       
	          unsigned char nb_symbols,
	          unsigned short nb_prefix_samples,        
		  short *twiddle_ifft,
		  unsigned short *rev,
		  Extension_t etype
		  );

#ifdef OPENAIR_LTE

/*! 
\brief This function implements the OFDM front end processor (FEP)
\param frame_parms LTE DL Frame Parameters
\param ue_common_vars LTE UE Common Vars
\param l symbol within slot (0..6/7)
\param Ns Slot number (0..19)
\param offset offset within rxdata (points to beginning of subframe)
\param no_prefix if 1 prefix is removed by HW 
*/

int slot_fep(LTE_DL_FRAME_PARMS *frame_parms,
	      LTE_UE_COMMON *ue_common_vars,
	      unsigned char l,
	      unsigned char Ns,
	      int offset,
	      int no_prefix);

int slot_fep_ul(LTE_DL_FRAME_PARMS *frame_parms,
		LTE_eNB_COMMON *eNb_common_vars,
		unsigned char l,
		unsigned char Ns,
		unsigned char eNb_id,
		int offset,
		int no_prefix);

#endif
/** @}*/
#endif
