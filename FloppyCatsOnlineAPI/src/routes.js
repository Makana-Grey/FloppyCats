import Router from 'koa-router'
import gameRoutes from './game/index.js'

const router = new Router()

router.use('/game', gameRoutes)

export default router.routes()
