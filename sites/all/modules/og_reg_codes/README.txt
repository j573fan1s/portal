README for og_reg_codes.module:

Compatible with Drupal 5.x. Requires the Organic Groups module.

This is an add-on for the Organic Groups module designed to facilitate users
joining a specific group upon registration (or afterwards as a member) on sites
that have a number of groups that is too large to easily browse through or show
in the registration form.

A new user will be auto-approved as member of a group when they supply a group 
code at registration. You may combine this feature with the usual use of groups
in the registration form. Users may also visit the "use group code" page (a tab
on the groups page) to join a group using a code, or to check a code.

Registration codes are only valid for groups that are "Open" or "Moderated". For
moderated groups, the membership will still need to be approved by a group 
manager. Codes cannot be used to join groups that are "Invite only" or "Closed".

The group registration codes are added into the "invite friend" e-mail message,
and are also viewable on each user's account page.

Registration codes may be made required or optional on the user registration 
page. Users who register and join a group by using a code may optionally be
assigned an additional role. Finally, the registration codes can be reset so 
that a new set is generated and all previous codes are invalidated.  Resetting
the codes has no effect on already subscribed users. You might want to reset,
for example, if a spammer is auto-registering accounts using an existing code.
It could also be useful, for example, in an educational situation to change the
codes at the end of a term/semester.

All the settings may be controled at the settings page at 
/admin/og/og-reg-codes.

---
written by Peter (pwolanin@drupal)

development sponsored by SEE, http://www.studenteducationalexchange.org
