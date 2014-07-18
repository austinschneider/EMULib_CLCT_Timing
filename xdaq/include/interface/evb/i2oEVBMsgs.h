#ifndef __i2oEVBMsgs_h__
#define __i2oEVBMsgs_h__

#include "i2o/i2o.h"


/**
 * \defgroup ExternalRuBuilderMsgs External RU builder I2O message frames
 * \brief <br>
 */

/**
 * \defgroup InternalRuBuilderMsgs Internal RU builder I2O message frames
 * \brief <br>
 */


///////////////////////////////////////////////////////////////////////////////
// External RU builder I2O messages                                          //
///////////////////////////////////////////////////////////////////////////////


/**
 * I2O message used to transfer a single block of event data.
 *
 * Events are composed of super-fragments, and super-fragment are cut up into
 * blocks for the purpose of data transmission.
 *
 * An event is composed of N super-fragments, where N is the total number of
 * RUs plus 1.  The first super-fragment contains the trigger data of the event
 * given to the EVM.  Each of the remaining super-fragments contains the
 * front-end data given to a RU.
 *
 * A super-fragment given to a RU is composed of fragments assembled by the FED
 * builder supplying data to that RU.  For the purposes of sending and
 * receiving data, the RU and BU applications do not see the boundaires of the
 * individual fragments within a super-fragment.  Instead, they treat a
 * super-fragment as an opaque set of data that are cut up into blocks for the
 * purpose of sending and receiving.  Therefore the boundaries of a
 * super-fragment's blocks do not neccessarily match the boundaries of a
 * super-fragment's fragments.
 *
 * The super-fragments of an event are numbered from 0.  The first
 * super-fragment (super-fragment 0) carries the trigger data of the event
 * from TA->EVM->BU->FU.  The remaining super-fragments (super-fragments 1 to
 * the number of RUs) carry the front-end data of the event from
 * RUI->RU->BU->FU.
 *
 * The blocks of a super-fragment are numbered from 0.  Please note that the
 * first super-fragment of an event, the one that contains an event's trigger
 * data, only contains one block.
 */
typedef struct _I2O_EVENT_DATA_BLOCK_MESSAGE_FRAME
{

    /**
     * I2O header.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;


    /**
     * Event number of the first-level trigger.
     *
     * When carrying trigger data from TA->EVM->BU->FU:
     * - This field is set by the TA
     * - This field is read by the EVM and BU
     *
     * When carrying front-end data from RUI->RU->BU->FU:
     * - This field is set by the RUI
     * - This field is read by the RU and BU
     */
    U32 eventNumber;


    /**
     * Total number of blocks in the current super-fragment.
     *
     * When carrying trigger data from TA->EVM->BU->FU:
     * - This field is set by the TA
     * - This field is read by the EVM, BU and FU
     *
     * When carrying front-end data from RUI->RU->BU->FU:
     * - This field is set by the RUI
     * - This field is read by the RU, BU and FU
     */
    U32 nbBlocksInSuperFragment;


    /**
     * Index of the this block within the current super-fragment.  Blocks
     * are indexed from 0.
     *
     * When carrying trigger data from TA->EVM->BU->FU:
     * - This field is set by the TA
     * - This field is read by the EVM, BU and FU
     *
     * When carrying front-end data from RUI->RU->BU->FU:
     * - This field is set by the RUI
     * - This field is read by the RU, BU and FU
     */
    U32 blockNb;


    /**
     * Identifier given to an event by the RU builder.  This identifier is
     * used for internal purposes of the RU builder.
     *
     * When carrying trigger data from TA->EVM->BU->FU:
     * - This field is set by the EVM
     * - This field is read by the BU
     *
     * When carrying front-end data from RUI->RU->BU->FU:
     * - This field is set by the RU
     * - This field is read by the BU
     */
    U32 eventId;


    /**
     * Identifies the BU resource being used to assemble the event to which
     * this block belongs.  The definition of what identifies a BU resource
     * is internal to the RU builder.
     *
     * When carrying trigger data from TA->EVM->BU->FU:
     * - This field is set by the EVM
     * - This field is read by the BU and FU
     *
     * When carrying front-end data from RUI->RU->BU->FU:
     * - This field is set by the RU
     * - This field is read by the BU and FU
     */
    U32 buResourceId;


    /**
     * Indentifies the event from the viewpoint of the FU requesting the
     * event
     *
     * When carrying trigger data from TA->EVM->BU->FU and when carrying
     * front-end data from RUI->RU->BU->FU:
     * - This field is set by the BU
     * - This field is read by the FU
     */
    U32 fuTransactionId;


    /**
     * Total number of super-fragments in the current event.
     *
     * When carrying trigger data from TA->EVM->BU->FU and when carrying
     * front-end data from RUI->RU->BU->FU:
     * - This field is set by the BU
     * - This field is read by the FU
     */
    U32 nbSuperFragmentsInEvent;


    /**
     * Index of this super-fragment within the current event.
     *
     * Super-fragments are indexed from 0.  Super-fragment 0 contains the
     * trigger data of an event given to the EVM.  Each of the remaining
     * super-fragments contains the front-end data given to a RU.
     *
     * When carrying trigger data from TA->EVM->BU->FU:
     * - This field is set by the EVM
     * - This field is read by the BU and FU
     *
     * When carrying front-end data from RUI->RU->BU->FU:
     * - This field is set by the RU
     * - This field is read by the BU and FU
     */
    U32 superFragmentNb;

} I2O_EVENT_DATA_BLOCK_MESSAGE_FRAME, *PI2O_EVENT_DATA_BLOCK_MESSAGE_FRAME;


/**
 * \ingroup ExternalRUBuilderMsgs
 * A single FU request to allocate a single BU resource.  This structure is
 * packed into a BU_ALLOCATE_MESSAGE_FRAME.
 */
typedef struct _BU_ALLOCATE
{
    /**
     * FU transaction id.
     */
    U32 fuTransactionId;

    /**
     * Fragment set identifier - ignored.
     */
    U32 fset;
} BU_ALLOCATE, *PBU_ALLOCATE;


/**
 * \ingroup ExternalRUBuilderMsgs
 * \brief Sent from FU to BU, to request that N events/resources be allocated
 * to the FU.
 */
typedef struct _I2O_BU_ALLOCATE_MESSAGE_FRAME {
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Number of events/resources to be allocated.
     */
    U32 n;

    /**
     * Padding for 64-bit alignment.
     */
    U32 padding;

    /**
     * The individual requests.
     */
    BU_ALLOCATE allocate[1];
} I2O_BU_ALLOCATE_MESSAGE_FRAME, *PI2O_BU_ALLOCATE_MESSAGE_FRAME;


/**
 * \ingroup ExternalRUBuilderMsgs
 * \brief Sent from FU to BU, to request that more of an event/resource should
 * be sent to the FU - ignored.
 */
typedef struct _I2O_BU_COLLECT_MESSAGE_FRAME {
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Id of the event/resource within the BU.
     */
    U32 buResourceId;

    /**
     * Fragment set identifier - ignored.
     */
    U32 fset;
} I2O_BU_COLLECT_MESSAGE_FRAME, *PI2O_BU_COLLECT_MESSAGE_FRAME;


/**
 * \ingroup ExternalRUBuilderMsgs
 * \brief Sent from FU to BU, to discard N events/resources in the BU.
 */
typedef struct _I2O_BU_DISCARD_MESSAGE_FRAME {
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Number of events/resources to be discarded.
     */
    U32 n;

    /**
     * Ids of the resources to be discarded.
     */
    U32 buResourceId[1];
} I2O_BU_DISCARD_MESSAGE_FRAME, *PI2O_BU_DISCARD_MESSAGE_FRAME;


/**
 * \ingroup ExternalRUBuilderMsgs
 * \brief Sent from EVM to BU signalling that the lumi section
 * has been completly processed.
 */
typedef struct _I2O_EVM_END_OF_LUMISECTION_MESSAGE_FRAME
{
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Run number
     */
    U32 runNumber;

    /**
     * Lumi section number
     */
    U32 lumiSection;
} I2O_EVM_END_OF_LUMISECTION_MESSAGE_FRAME, *PI2O_EVM_END_OF_LUMISECTION_MESSAGE_FRAME;


/**
 * \ingroup ExternalRUBuilderMsgs
 * \brief Sent from EVM to TA, giving the TA one or more credits to send
 * trigger data to the EVM.
 */
typedef struct _I2O_TA_CREDIT_MESSAGE_FRAME
{
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Number of credits.
     */
    U32 nbCredits;

    /**
     * Padding for 64-bits.
     */
    U32 padding;
} I2O_TA_CREDIT_MESSAGE_FRAME, *PI2O_TA_CREDIT_MESSAGE_FRAME;


///////////////////////////////////////////////////////////////////////////////
// Internal RU builder messages                                              //
///////////////////////////////////////////////////////////////////////////////


/**
 * \ingroup InternalRUBuilderMsgs
 * \brief A request for an event id and/or a released event id.
 */
typedef struct _EvtIdRqstAndOrRelease
{
    /**
     * 0: Requesting an event id
     * 1: Releasing  an event id and requesting another
     * 2: Releasing  an event id
     */
    U32 type;

    /**
     * Event id of event to be released - only filled when releasing.
     */
    U32 eventId;     ///< Only filled when releasing

    /**
     * Event number of event to be released - only filled when releasing.
     */
    U32 eventNumber;

    /**
     * Id of the resource within the BU - always filled.
     */
    U32 resourceId;
} EvtIdRqstAndOrRelease, *PEvtIdRqstAndOrRelease;


/**
 * \ingroup InternalRUBuilderMsgs
 * \brief BU to EVM message that contains zero or more requests for event ids
 * plus zero or more released event ids.
 */
typedef struct _EvtIdRqstsAndOrReleasesMsg
{
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Message sequence number.
     */
    U32 msgSeqNb;

    /**
     * Index of the source application.
     *
     * Indices are used to facilitate efficient lookups.
     */
    U32 srcIndex;

    /**
     * Number of elements.
     */
    U32 nbElements;

    /**
     * Padding for 64-bits.
     */
    U32 padding;

    /**
     * Elements.
     */
    EvtIdRqstAndOrRelease elements[1];
} EvtIdRqstsAndOrReleasesMsg, *PEvtIdRqstsAndOrReleasesMsg;


/**
 * \ingroup InternalRUBuilderMsgs
 * \brief An event id and a trigger pair to be packed into an
 * EvtIdTrigPairsMsg.
 *
 * <b>Note</b>
 *
 * This element type IS and MUST be a multiple of 4 bytes.
 */
typedef struct _EvtIdTrigPair
{
    /**
     * Event id of the event.
     */
    U32 eventId;

    /**
     * Event number (from trigger) of the event.
     */
    U32 eventNumber;
} EvtIdTrigPair, *PEvtIdTrigPair;


/**
 * \ingroup InternalRUBuilderMsgs
 * \brief EVM to RU meesage that contains one or more event id / trigger pairs.
 */
typedef struct _EvtIdTrigPairsMsg
{
    /**
     * I2O information.
     */
    I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

    /**
     * Message sequence number.
     */
    U32 msgSeqNb;

    /**
     * Number of elements.
     */
    U32 nbElements;

    /**
     * Elements.
     */
    EvtIdTrigPair elements[1];
} EvtIdTrigPairsMsg, *PEvtIdTrigPairsMsg;


/**
 * \ingroup InternalRUBuilderMsgs
 * \brief Contains the event id and trigger event number of the event fragment
 * wanted and the id of the resource that will be used to assemble the whole
 * event.
 */
typedef struct _RqstForFrag
{
    /**
     * Event id of event.
     */
    U32 eventId;

    /**
     * Event number of event.
     */
    U32 eventNumber;

    /**
     * Id of the BU resource used to assemble the event.
     */
    U32 buResourceId;
} RqstForFrag, *PRqstForFrag;


/**
 * \ingroup InternalRUBuilderMsgs
 * \brief BU to RU message that contains one or more requests for event
 * fragments, where each request is represented by the event id of the event
 * fragment wanted and the id of the resource that will be used to assemble
 * the whole event.
 */
typedef struct _RqstForFragsMsg
{
   /**
    * I2O information.
    */
   I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;

   /**
    * Message sequence number.
    */
   U32 msgSeqNb;

   /**
    * Index of the source application.
    *
    * Indices are used to facilitate efficient lookups.
    */
   U32 srcIndex;

   /**
    * Number of elements.
    */
   U32 nbElements;

    /**
     * Elements.
     */
    RqstForFrag elements[1];
} RqstForFragsMsg, *PRqstForFragsMsg;


#endif
