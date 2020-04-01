/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Parent system
 *
 * =======================================================================
 */

#include "header/local.h"

void set_child_movement( edict_t *self )
{
	edict_t	*e;
	edict_t	*parent;
	vec3_t	forward, right, up;
	vec3_t	angles, amove;
	vec3_t	offset;
	vec3_t	delta_angles;
	qboolean	is_monster;

	if( !self->inuse )
		return;

	e = self->child_next;
	parent = self;
	while( e != NULL )
	{
restart:
		if(!e->inuse) break;

		VectorSubtract( self->s.angles, e->parent_attach_angles, delta_angles );
		AngleVectors( delta_angles, forward, right, up );
		VectorNegate( right, right );

		// remove gibbed monsters from the chain
		if( e->svflags & SVF_MONSTER )
		{
			if( e->health <= e->gib_health )
			{
				parent->child_next = e->child_next;
				e = e->child_next;
				if( e ) goto restart;
				break;
			}
			is_monster = true;
		}
		else
		{
			is_monster = false;
		}

		// For all but func_button and func_door, move origin and match velocities
		if(( strcmp( e->classname, "func_door" )) && (strcmp( e->classname, "func_button" )))
		{
			VectorMA( self->s.origin, e->parent_offset[0], forward, e->s.origin );
			VectorMA( e->s.origin, e->parent_offset[1], right, e->s.origin );
			VectorMA( e->s.origin, e->parent_offset[2], up, e->s.origin );
			VectorCopy( self->velocity, e->velocity );
		}

		// If parent is spinning, add appropriate velocities
		VectorSubtract( e->s.origin, self->s.origin, offset );
		if( self->avelocity[PITCH] != 0 )
		{
			e->velocity[2] -= offset[0] * self->avelocity[PITCH] * M_PI / 180;
			e->velocity[0] += offset[2] * self->avelocity[PITCH] * M_PI / 180;
		}

		if( self->avelocity[YAW] != 0 )
		{
			e->velocity[0] -= offset[1] * self->avelocity[YAW] * M_PI / 180.;
			e->velocity[1] += offset[0] * self->avelocity[YAW] * M_PI / 180.;
		}

		if( self->avelocity[ROLL] != 0 )
		{
			e->velocity[1] -= offset[2] * self->avelocity[ROLL] * M_PI / 180;
			e->velocity[2] += offset[1] * self->avelocity[ROLL] * M_PI / 180;
		}

		VectorScale( self->avelocity, FRAMETIME, amove );

		// Special cases:
		// Func_door/func_button and trigger fields
		if( (!strcmp( e->classname, "func_door" )) || (!strcmp( e->classname, "func_button" )) )
		{
			VectorAdd( e->s.angles, e->org_angles, angles );
			G_SetMovedir( angles, e->movedir );
			VectorMA( self->s.origin, e->parent_offset[0], forward, e->pos1 );
			VectorMA( e->pos1, e->parent_offset[1], right, e->pos1 );
			VectorMA( e->pos1, e->parent_offset[2], up, e->pos1 );
			VectorMA( e->pos1, e->moveinfo.distance, e->movedir, e->pos2 );
			VectorCopy( e->pos1, e->moveinfo.start_origin );
			VectorCopy( e->s.angles, e->moveinfo.start_angles );
			VectorCopy( e->pos2, e->moveinfo.end_origin );
			VectorCopy( e->s.angles, e->moveinfo.end_angles );

			if( e->moveinfo.state == STATE_BOTTOM || e->moveinfo.state == STATE_TOP )
			{
				// Velocities for door/button movement are handled in normal
				// movement routines
				VectorCopy(self->velocity,e->velocity);
				// Sanity insurance:
				if(e->moveinfo.state == STATE_BOTTOM)
				{
					VectorCopy(e->pos1, e->s.origin);
				}
				else
				{
					VectorCopy(e->pos2, e->s.origin);
				}
			}
		}

		if(amove[YAW])
		{
			// transform AABB
			if( (!strcmp( e->classname, "func_door" )) || (!strcmp( e->classname, "func_button" )) || (e->solid == SOLID_TRIGGER) )
			{
				float	ca, sa, yaw;
				vec3_t	p00, p01, p10, p11;

				// Adjust bounding box for yaw
				yaw = e->s.angles[YAW] * M_PI / 180.;
				ca  = cos( yaw );
				sa  = sin( yaw );
				p00[0] = e->org_mins[0] * ca - e->org_mins[1] * sa;
				p00[1] = e->org_mins[1] * ca + e->org_mins[0] * sa;
				p01[0] = e->org_mins[0] * ca - e->org_maxs[1] * sa;
				p01[1] = e->org_maxs[1] * ca + e->org_mins[0] * sa;
				p10[0] = e->org_maxs[0] * ca - e->org_mins[1] * sa;
				p10[1] = e->org_mins[1] * ca + e->org_maxs[0] * sa;
				p11[0] = e->org_maxs[0] * ca - e->org_maxs[1] * sa;
				p11[1] = e->org_maxs[1] * ca + e->org_maxs[0] * sa;
				e->mins[0] = p00[0];
				e->mins[0] = min( e->mins[0], p01[0] );
				e->mins[0] = min( e->mins[0], p10[0] );
				e->mins[0] = min( e->mins[0], p11[0] );
				e->mins[1] = p00[1];
				e->mins[1] = min( e->mins[1], p01[1] );
				e->mins[1] = min( e->mins[1], p10[1] );
				e->mins[1] = min( e->mins[1], p11[1] );
				e->maxs[0] = p00[0];
				e->maxs[0] = max( e->maxs[0], p01[0] );
				e->maxs[0] = max( e->maxs[0], p10[0] );
				e->maxs[0] = max( e->maxs[0], p11[0] );
				e->maxs[1] = p00[1];
				e->maxs[1] = max( e->maxs[1], p01[1] );
				e->maxs[1] = max( e->maxs[1], p10[1] );
				e->maxs[1] = max( e->maxs[1], p11[1] );
			}
		}

		e->s.event = self->s.event;
		gi.linkentity( e );
		parent = e;
		e = e->child_next;
	}
}

void parent_init( edict_t *ent )
{
	edict_t *e, *child;

	// unnamed entities can't be moves with parents
	if( !ent->targetname ) return;

	child = G_Find( NULL, FOFS( parent), ent->targetname );
	e = ent;

	while( child )
	{
		child->parent_ent = ent;
		// Copy parent's current angles to the child. They SHOULD be 0,0,0 at this point
		// for all currently supported parents, but ya never know.
		VectorCopy( ent->s.angles, child->parent_attach_angles );
		if( child->org_movetype < 0 )
			child->org_movetype = child->movetype;
		if( child->movetype != MOVETYPE_NONE )
			child->movetype = MOVETYPE_PUSH;
		VectorCopy( child->mins, child->org_mins );
		VectorCopy( child->maxs, child->org_maxs );
		VectorSubtract( child->s.origin, ent->s.origin, child->parent_offset );
		e->child_next = child;
		e = child;
		child = G_Find( child, FOFS( parent ), ent->targetname );
	}
}

void parent_update( edict_t *self )
{
	if( self->moveinfo.state == STATE_BOTTOM )
	{
		VectorCopy( self->s.origin, self->pos1 );
		VectorMA( self->pos1, self->moveinfo.distance, self->movedir, self->pos2 );
	}
	else if( self->moveinfo.state == STATE_TOP )
	{
		VectorCopy( self->s.origin, self->pos2 );
		VectorMA( self->pos2, -self->moveinfo.distance, self->movedir, self->pos1 );
	}

	VectorCopy( self->pos1, self->moveinfo.start_origin );
	VectorCopy( self->pos2, self->moveinfo.end_origin );
}
