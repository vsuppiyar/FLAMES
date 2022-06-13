#include <vector>
#include <string>
#include <codecvt>
#include <Rcpp.h>

#include "../utility/bam.h"
#include "../utility/cigars.h"
#include "BamRecord.h"


/*  takes a flag int, converts it to all of the properties it encodes for 
*/
Flag
read_flag(int n)
{
    Flag flag;

    flag.read_paired                               = (n & (1<<0));
    flag.read_mapped_in_proper_pair                = (n & (1<<1));
    flag.read_unmapped                             = (n & (1<<2));
    flag.mate_unmapped                             = (n & (1<<3));
    flag.read_reverse_strand                       = (n & (1<<4));
    flag.mate_reverse_strand                       = (n & (1<<5));
    flag.first_in_pair                             = (n & (1<<6));
    flag.second_in_pair                            = (n & (1<<7));
    flag.not_primary_alignment                     = (n & (1<<8));
    flag.read_fails_platform_vendor_quality_checks = (n & (1<<9));
    flag.read_is_PCR_or_optical_duplicate          = (n & (1<<10));
    flag.supplementary_alignment                   = (n & (1<<11));

    return flag;
}

/*  takes a single bam entry, converts it into a BAMRecord struct
*/
BAMRecord
read_record(const bam1_t * b, const bam_header_t * header)
{
    BAMRecord rec;
    rec.reference_start = bam_alignment_start(b);
    rec.reference_end = bam_alignment_end(b);
    rec.reference_name = std::string(header->target_name[b->core.tid]);
    rec.AS_tag = bam_aux2i(bam_aux_get(b, "AS"));
    rec.query_alignment_length = b->core.l_qseq;
    rec.read_name = std::string(bam1_qname(b));
    rec.mapping_quality = (int)bam_mapping_qual(b);
    rec.cigar = generate_cigar_pairs(b);
	rec.cigar_string = generate_cigar(rec.cigar);
    rec.flag = read_flag(b->core.flag);
    return rec;
}