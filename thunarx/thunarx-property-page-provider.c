/* $Id: thunarx-property-page-provider.c 20531 2006-03-24 14:46:35Z benny $ */
/*-
 * Copyright (c) 2005-2006 Benedikt Meurer <benny@xfce.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <thunarx/thunarx-private.h>
#include <thunarx/thunarx-property-page-provider.h>
#include <thunarx/thunarx-alias.h>



GType
thunarx_property_page_provider_get_type (void)
{
  static GType type = G_TYPE_INVALID;

  if (G_UNLIKELY (type == G_TYPE_INVALID))
    {
      static const GTypeInfo info =
      {
        sizeof (ThunarxPropertyPageProviderIface),
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        0,
        NULL,
        NULL,
      };

      /* register the property page provider interface */
      type = g_type_register_static (G_TYPE_INTERFACE, I_("ThunarxPropertyPageProvider"), &info, 0);
      g_type_interface_add_prerequisite (type, G_TYPE_OBJECT);
    }

  return type;
}



/**
 * thunarx_property_page_provider_get_pages:
 * @provider : a #ThunarxPropertyPageProvider.
 * @files    : the list of #ThunarxFileInfo<!---->s for which a properties dialog will be displayed.
 *
 * Returns the list of #ThunarxPropertyPage<!---->s that @provider has to offer for @files.
 *
 * Extensions that implement this interface, must first check whether they support all the
 * #ThunarxFileInfo<!---->s in the list of @files. Most extensions will probably only support
 * #ThunarxPropertyPage<!---->s for exactly one file of a certain type. For example an MP3-Tag
 * editor property page will most probably support only a single audio file, and so the method
 * would be implemented like this
 * <informalexample><programlisting>
 * GList*
 * tag_provider_get_pages (ThunarxPropertyPageProvider *property_page_provider,
 *                         GList                       *files)
 * {
 *   if (g_list_length (files) != 1)
 *     return NULL;
 *   else if (!thunarx_file_info_has_mime_type (files->data, "audio/mp3"))
 *     return NULL;
 *   else
 *     return g_list_append (NULL, tag_page_new (files->data));
 * }
 * </programlisting></informalexample>
 * where tag_page_new() allocates a new #TagPage instance for a #ThunarxFileInfo object
 * passed to it. See the description of the #ThunarxPropertyPage class for additional
 * information about the #TagPage example class.
 *
 * As a special note, this method automatically takes a reference on the
 * @provider for every #ThunarxPropertyPage object returned from the real implementation
 * of this method in @provider. This is to make sure that the extension stays
 * in memory for atleast the time that the pages are used. If the extension
 * wants to stay in memory for a longer time, it'll need to take care of this
 * itself (e.g. by taking an additional reference on the @provider itself,
 * that's released at a later time).
 *
 * The caller is responsible to free the returned list of pages using
 * something like this when no longer needed:
 * <informalexample><programlisting>
 * g_list_foreach (list, (GFunc) g_object_ref, NULL);
 * g_list_foreach (list, (GFunc) gtk_object_sink, NULL);
 * g_list_foreach (list, (GFunc) g_object_unref, NULL);
 * g_list_free (list);
 * </programlisting></informalexample>
 *
 * Return value: the list of #ThunarxPropertyPage<!---->s that @provider has to offer
 *               for @files.
 **/
GList*
thunarx_property_page_provider_get_pages (ThunarxPropertyPageProvider *provider,
                                          GList                       *files)
{
  GList *pages;

  g_return_val_if_fail (THUNARX_IS_PROPERTY_PAGE_PROVIDER (provider), NULL);
  g_return_val_if_fail (files != NULL, NULL);

  if (THUNARX_PROPERTY_PAGE_PROVIDER_GET_IFACE (provider)->get_pages != NULL)
    {
      /* query the property pages from the implementation */
      pages = (*THUNARX_PROPERTY_PAGE_PROVIDER_GET_IFACE (provider)->get_pages) (provider, files);

      /* take a reference on the provider for each page */
      thunarx_object_list_take_reference (pages, provider);
    }
  else
    {
      pages = NULL;
    }

  return pages;
}



#define __THUNARX_PROPERTY_PAGE_PROVIDER_C__
#include <thunarx/thunarx-aliasdef.c>