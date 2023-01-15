// // Created by tomasz on 4/15/19.
//
// #include "VisibleBody.hpp"
// #include "Game.hpp"
// #include "Casts.hpp"
// #include "Drawable.hpp"
//
// VisibleBody::VisibleBody(const b2BodyDef& definition):
//     Body( definition ){
//     // nothing
// }
//
// sf::Drawable& VisibleBody::makeGraphicsFromFixture(const b2Fixture& fixture){
//     if( fixture.GetShape()->GetType() == b2Shape::Type::e_polygon ){
//         _drawables.emplace_back(
//             [fixture](){
//                 auto graphic = std::make_unique<Drawable<sf::ConvexShape>>(*window);
//                 auto shape = reinterpret_cast<const b2PolygonShape*>(fixture.GetShape());
//
//                 graphic->setPointCount( shape->m_count );
//                 for(auto i = 0; i < shape->m_count; i++){
//                     graphic->setPoint( i, vector( shape->m_vertices[i] ) );
//                 }
//                 return std::move( graphic );
//             }()
//         );
//     }else if( fixture.GetShape()->GetType() == b2Shape::Type::e_circle ){
//         _drawables.emplace_back( std::make_unique<Drawable<sf::CircleShape>>( *window, fixture.GetShape()->m_radius ) );
//     }
//     return *_drawables.back();
// }
//
// VisibleBody::FixtureData VisibleBody::createFixture(const b2FixtureDef& fixtureDef){
//     auto& fixture = *Body::get()->CreateFixture( &fixtureDef );
//     auto& graphics = makeGraphicsFromFixture( fixture );
//     return {fixture, graphics};
// }
//
// VisibleBody::FixtureData VisibleBody::createFixture(const b2Shape& shape, float32 density){
//     auto& fixture = *Body::get()->CreateFixture( &shape, density );
//     auto& graphics = makeGraphicsFromFixture( fixture );
//     return {fixture, graphics};
// }
