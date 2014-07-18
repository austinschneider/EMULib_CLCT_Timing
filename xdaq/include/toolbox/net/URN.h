// $Id: URN.h,v 1.3 2008/07/18 15:27:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

/**
 * The embodiment of a Uniform Resource Name (URN) as a class.
 *
 * <b><i>URN SYNTAX:</i></b>
 * <P>
 * URNs take the form:
 * <PRE>
 *   identifier:namespace:namespace specific string</code>
 *   urn:&lt;NID&gt;:&lt;NSS&gt;
 * </PRE>
 * <P>
 * URN example:
 * <PRE>
 *   urn:vrml:umel:texture/wood/oak.gif
 * </PRE>
 * <P>
 * For details on URNs see the IETF working group:
 * <A HREF="http://www.ietf.org/html.charters/urn-charter.html">URN</A>
 * <P>
 *
 * A URN is used to define a resource without specifying where it is to be
 * found. A Resovler Discovery Service is used to discover a resolver that
 * can take the URN and turn it into a particular service. A URN is not
 * always used to extract that actual resource. Other services as defined
 * <A HREF=http://info.internet.isi.edu/in-notes/rfc/files/rfc2168.txt">RFC 2168</A>
 * are available.
 * <P>
 * for a description of URN/URL/URC concepts, see also:
 * <A HREF=http://info.internet.isi.edu/in-notes/rfc/files/rfc2169.txt">RFC 2169</A>
 * <P>
 * The system property <CODE>urn.resolve.confirm</CODE> is used to determine
 * the behaviour from here. If the property is <CODE>false</CODE> then it will
 * return the first found resolver without testing it. If the property is
 * set to <CODE>true</CODE> then the URN class will attempt to open the name
 * resource to confirm that it may be fetched from the nominated source. If it
 * cannot, the search continues until one can be or options run out, in which
 * case <CODE>null</CODE> is returned. The default value is <CODE>false</CODE>.
 * It may be overridden on a case by case basis using the appropriate flag in
 * the constructor.
 * <P>
 *
 * <B>Services</B>
 * <P>
 *
 * The methods match the services requests that are defined for URNs in
 * RFC 2168 (although there is a draft update). However, there is some
 * adaptations of the behaviour. RFC2168 defines list services that assume
 * only a single RDS is available for a URN. However, this implementation
 * allows for multiple RDS implementations to be consulted. When requesting
 * lists of things (I2Xs services) the implementation firsts requests the RDSs
 * for all I2Xs resolutions. Following this, it then asks all the resolvers
 * for the singleton versions (I2X services) and adds any found items to the
 * list to return.
 * <P>
 * The idea of this implementation is that although a particular RDS may not
 * be able to return a list of items, a list may be constructed from a
 * collection of single instances - even if this list is only one item long.
 * This raises some fundamental questions regarding resolver services and
 * the differences between a list and a single value (which is a list of
 * length one).
 * <P>
 */

#ifndef _toolbox_net_URN_h_
#define _toolbox_net_URN_h_
 
#include <string>
#include <vector>
#include "toolbox/net/exception/MalformedURN.h"
#include "toolbox/exception/UnsupportedService.h"
#include "toolbox/net/URL.h"
#include "toolbox/net/URI.h"
#include "toolbox/net/URC.h"

namespace toolbox {
namespace net {

class URN
{
	private:

  	// Variables to hold parts of a parsed URN follow:

  	/** The fully urn as passed to this class with whitespace stripped */
  	std::string urn_;

  	/**
	* The name of the organization which defines
	* the rules on name allocation for this URN.
	* Example: "vrml"
	*/
  	std::string namespace_;

	/**
	* The namespace specific string.
	* Example: "images/buttons/start.gif"
	*/
	std::string reference_;
	
	public:

	/**
	* Creates a URN object from the string representation.
	* <P>
	* The default implementation is to not confirm that the request can be
	* satisfied by the first available RDS.
	*
	* @param spec the <code>String</code> to parse as a URN.
	* @exception MalformedURNException  If the spec String specifies an
	*   incomplete or invalid URN.
	*/
  	URN (std::string spec) throw (toolbox::net::exception::MalformedURN);

  /**
   * Create a new URN instance from the component parts. Checks to make sure
   * that the NID and NSS are not null.
   *
   * @param nid The namespace identifier portion of this URN
   * @param nss The namespace specific string portion of this URN
   * @throws NullPointerException One of the parameters was null
   */
  URN(std::string nid, std::string nss) throw (toolbox::net::exception::MalformedURN);

  /**
   * Returns the namespace of this <code>URN</code>.
   *
   * @return  the namespace of this <code>URN</code>.
   */
  std::string getNamespace();

  /**
   * Returns the namespace specific portion of this <code>URN</code>.
   *
   * @return  the NSS of this <code>URN</code>.
   */
  std::string getNSS();

  /**
   * N2L service request. Get the URL that represents this URN. Whether this
   * results in a legal URL that really represents the URN is dependent on the
   * confirm property.
   * <P>
   * If a URL representation of this URN cannot be found through the resolver
   * service then this method returns null.
   *
   * @return The URL representing this URN or null
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   */
  toolbox::net::URL getURL() throw (toolbox::exception::UnsupportedService);

  /**
   * I2Ls service request. Get the list of possible URLs that represents this
   * URN. Whether this results in a legal URL that really represents the URN
   * is dependent on the confirm property.
   * <P>
   * If a URL representation of this URN cannot be found through the resolver
   * service then this method returns null.
   *
   * @return The list of URL representing this URN or null
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   */
   std::vector<toolbox::net::URL> getURLList() throw (toolbox::exception::UnsupportedService);

  /**
   * I2C service request. Get the first URC that describes this URN.
   * If a URC cannot be determined for this URN then null is returned.
   *
   * @return The URC describing this URN.
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   */
  toolbox::net::URC getURC() throw (toolbox::exception::UnsupportedService);

  /**
   * N2C service request. Get the list of URCs that describes this URN.
   * If a URC cannot be determined for this URN then null is returned.
   *
   * @return The URC describing this URN.
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   */
  std::vector<toolbox::net::URC> getURCList() throw (toolbox::exception::UnsupportedService);

  /**
   * N2Ns service request. Get the list of possible URNs that are also
   * equivalent descriptors of this resource. If no alternate representations
   * are available, then null is returned.
   *
   * @return The list of equivalent URNs
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   */
  std::vector<URN> getURNList() throw (toolbox::exception::UnsupportedService);

  /**
   * Establish a connection to the named resource. This partially maps the
   * N2R service request in providing a representation of the connection to
   * the resource without actually supply the resource itself. The resource
   * itself can be then obtained using the methods of the ResouceConnection
   * class.
   *
   * @return A reference to the connection to the resource.
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   * @see ResourceConnection
   */
   /*
  public ResourceConnection getResource()
    throws UnsupportedServiceException, IOException
 
  */

  /**
   * Establish a connection to all possible resolutions of this resource. This
   * partially maps to the N2Rs service request in providing all possible
   * representations of the URN without actually fetching the resource itself.
   * The resources themselves may be obtained using the methods of the
   * ResourceConnection class.
   *
   * @return The list of connections to resources
   * @exception UnsupportedServiceException Resolution of the requested service
   *   type for this URN is not available
   * @see ResourceConnection
   */
   /*
  public ResourceConnection[] getResourceList()
    throws UnsupportedServiceException, IOException
  
*/

  /**
   * Create a string representation of the URI.
   *
   * @return The string representation of this object
   */
  std::string toString() const;

  /**
   * Test for equality between this URN and any other URI. Implements the I=I
   * service request. If the object is not a URI then false is immediately
   * returned otherwise the alternate version of this method is called.
   *
   * @param o The object to compare against
   * @return true if they are equivalent URI
   */
  bool equals(const URN& urn);

  /**
   * Test for equality between this URN and any other URI. Implements the I=I
   * service request.
   * Exmaples for URL, URN, URI:
   * 
   * URL - http://www.pippo.org/faq.html
   * URN - urn:myns:pippo.org/faq.html#Chapter25
   * URI - http://www.pippo.org/faq.html#Chapter25
   *
   * See also: <A href="www.pierobo.org/iis/url.htm>this link</a>
   * <P>
   *
   * @param uri The URI to compare against
   * @return true if they are equivalent URI
   */
  bool equals(const toolbox::net::URI& uri) throw (toolbox::exception::UnsupportedService);
  
};

} // end net
} // end toolbox

#endif
